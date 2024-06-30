#ifndef SCHRODINGERSOLVER_H
#define SCHRODINGERSOLVER_H
#include "Runge_Kutta_4.h"
#include "integrate.h"
#include <functional>
#include <vector>

#define E 1
namespace plt = matplotlibcpp;
using potentialFunction = std::function<double(double/*x*/)>;
std::vector<char> ALLOWED_EXPECTATION_VALUES = {'x'};

class wavefunction{
private:
    std::vector<double> wavefunctionValues;
    std::vector<double> x;
    potentialFunction V;

    bool solved = 0;

    std::pair<double, double> ode_system(double x, double y, double dydx) {
        double dyPrimedx = 2*y*V(x) - 2*y*E;
        return {dydx, dyPrimedx};
    }

public:
    wavefunction(potentialFunction V) : V(V) {}

    void solve(double x0, double y0, double dydx0) {
        solved = 1;

        const int length = 300;
		double h = 0.01;

		std::pair<double*, double*> results = rk4_paired<length>(std::bind(&wavefunction::ode_system, this,
            std::placeholders::_1,
                std::placeholders::_2,
                    std::placeholders::_3),
                        y0, dydx0, x0, h);

        for (int i = 0; i < length; i++)
		    x.push_back(x0 + i * h);
		
		wavefunctionValues = std::vector<double>(results.first, results.first + length);

		delete[] results.first;
		delete[] results.second;

        //normalization
        std::vector<double> modSquared;
        for (int i = 0; i < wavefunctionValues.size(); i++)
            modSquared.push_back(wavefunctionValues[i]);
        
        double eta = std::sqrt(1.0 / integrateOverAllKnownValues(modSquared, 0.01)); //normalization constant
        for (int i = 0; i < wavefunctionValues.size(); i++)
            wavefunctionValues[i] *= (eta);

        plt::plot(x, wavefunctionValues);
        plt::title("ψ");
		plt::save("../saves/wavefunction.png");
    }

    double expectation_value(char operatorChar){
        if (std::find(ALLOWED_EXPECTATION_VALUES.begin(), ALLOWED_EXPECTATION_VALUES.end(), operatorChar) == ALLOWED_EXPECTATION_VALUES.end())
            throw std::invalid_argument("Not a valid expectation value! Try: x, p");
        
        std::vector<double> toIntegrateOver(wavefunctionValues.size());

        switch (operatorChar) {
            case 'x':
                for (int i = 0; i < wavefunctionValues.size(); i++)
                    toIntegrateOver[i] = wavefunctionValues[i] * x[i] * wavefunctionValues[i];
                break;
            default:
                throw std::invalid_argument("Operator not implemented yet.");
        }

        return integrateOverAllKnownValues(toIntegrateOver, 0.01);
    }
    
};

#endif