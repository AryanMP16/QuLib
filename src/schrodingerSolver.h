#ifndef SCHRODINGERSOLVER_H
#define SCHRODINGERSOLVER_H
#include "Runge_Kutta_4.h"
#include "integrate.h"
#include "complex.h"
#include <functional>
#include <vector>

#define E 1
#define PI 3.141592653589793
namespace plt = matplotlibcpp;
using potentialFunction = std::function<double(double/*x*/)>;
std::vector<char> ALLOWED_EXPECTATION_VALUES = {'x', 'p'};

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

    void solve(double x0, double y0, double dydx0, std::string title) {
        solved = 1;

        const int length = 3000;
		double h = 0.001;

		std::pair<double*, double*> results = rk4_paired<length>(std::bind(&wavefunction::ode_system, this,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3),
            y0, dydx0, x0, h);

        x.clear();
        wavefunctionValues.clear();
        for (int i = 0; i < length; i++) {
            x.push_back(x0 + i * h);
            wavefunctionValues.push_back(results.first[i]);
        }

		delete[] results.first;
		delete[] results.second;

        //normalization
        std::vector<double> modSquared(wavefunctionValues.size());
        for (int i = 0; i < wavefunctionValues.size(); i++)
            modSquared.push_back(wavefunctionValues[i] * wavefunctionValues[i]);
        
        double eta = std::sqrt(1.0 / integrateOverAllKnownValues(modSquared, 0.001)); //normalization constant
        for (int i = 0; i < wavefunctionValues.size(); i++)
            wavefunctionValues[i] *= (eta);

        plt::clf();
        plt::plot(x, wavefunctionValues);
        plt::title("ψ " + title);
		plt::save("../saves/"+ title + ".png");
    }

    double expectation_value(char operatorChar){
        if (std::find(ALLOWED_EXPECTATION_VALUES.begin(), ALLOWED_EXPECTATION_VALUES.end(), operatorChar) == ALLOWED_EXPECTATION_VALUES.end())
            throw std::invalid_argument("Not a valid expectation value! Try: x, p");
        
        std::vector<double> toIntegrateOver(wavefunctionValues.size());
        std::pair<std::vector<complexNumber<double>>, std::vector<double>> psi_p;//used for p expectation value

        switch (operatorChar) {
            case 'x':
                for (int i = 0; i < wavefunctionValues.size(); i++)
                    toIntegrateOver[i] = wavefunctionValues[i] * x[i] * wavefunctionValues[i];
                break;
            case 'p':
                //physics logic supporting this:
                //<p> = <ψ|p|ψ> = ∫ ψ*(x) (-iħ d/dx) ψ(x) dx
                //<p|ψ> = ψ(p) = ∫ e^{-ipx/ħ} ψ(x) dx, the Fourier transform
                //<p> = <ψ|p|ψ> = ∫ ψ*(p) p ψ(p) dp
                //So all we need to do is take the fourier transform of the function we already have
                psi_p = FourierTransform(wavefunctionValues, x);
                for (int i = 0; i < psi_p.first.size(); i++)
                    toIntegrateOver[i] = psi_p.first[i].get_real() * psi_p.second[i] * psi_p.first[i].get_real();
                break;
            default:
                throw std::invalid_argument("Operator not implemented yet.");
        }

        return integrateOverAllKnownValues(toIntegrateOver, 0.001);
    }

    std::pair<std::vector<complexNumber<double>>, std::vector<double>> FourierTransform(std::vector<double> fxn, std::vector<double> x_values) {
        double N = fxn.size();
        double deltaX = x_values[1] - x_values[0]; //this is valid because all instances of x will have uniform spacing

        std::vector<complexNumber<double>> FT(N);
        std::vector<double> p_vec(N);

        for (int k = 0; k < N; k++){
            double p = 2 * PI * (static_cast<int>(k) - static_cast<int>(N) / 2) / (N * deltaX);
            complexNumber<double> sum(0.0, 0.0);
            
            for (int j = 0; j < N; j++){
                double angle = p * x_values[j];
                complexNumber<double> eulers_equation(std::cos(angle), -std::sin(angle));
                sum += eulers_equation * fxn[j];
            }
            FT[k] = sum * deltaX;
            p_vec[k] = p;
        }

        return std::make_pair(FT, p_vec);
    }
    
};

#endif