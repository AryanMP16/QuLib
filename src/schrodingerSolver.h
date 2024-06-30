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
        
        double eta = 1.0 / integrateOverAllKnownValues(modSquared, 0.01); //normalization constant
        for (int i = 0; i < wavefunctionValues.size(); i++)
            wavefunctionValues[i] /= (eta);

        plt::plot(x, wavefunctionValues);
        plt::title("ψ");
		plt::save("../saves/wavefunction.png");
    }

    double expectation_value(char operatorChar){
        int i;
        for (i = 0; i < ALLOWED_EXPECTATION_VALUES.size(); i++) {
            if (operatorChar == ALLOWED_EXPECTATION_VALUES[i])
                break;
        }
        if (i == ALLOWED_EXPECTATION_VALUES.size())
            throw std::invalid_argument("Not a valid expectation value! Try: x, p");
        
        switch (operatorChar) {
            case 'x':
                std::vector<double> toIntegrateOver;
                for (int i = 0; i < wavefunctionValues.size(); i++)
                    toIntegrateOver.push_back(wavefunctionValues[i] * x[i] * wavefunctionValues[i]);
                
                return integrateOverAllKnownValues(toIntegrateOver, 0.01); //this is the expectation value
                break;
        }

        return -9999999999999999; //makes compiler happy because it knows that there's something to return,
                                  //even though we know that if one of the cases is not entered, an error will be thrown
    }
    
};

#endif