#ifndef SCHRODINGERSOLVER_H
#define SCHRODINGERSOLVER_H
#include "Runge_Kutta_4.h"
#include <functional>
#include <vector>
#define E 1

namespace plt = matplotlibcpp;

using potentialFunction = std::function<double(double/*x*/)>;

class wavefunction{
private:
    std::vector<double> wavefunctionValues;
    std::vector<double> x;
    potentialFunction V;

    std::pair<double, double> ode_system(double x, double y, double dydx) {
        double dyPrimedx = 2*y*V(x) - 2*y*E;
        return {dydx, dyPrimedx};
    }
public:
    wavefunction(potentialFunction V) : V(V) {}

    void solve(double x0, double y0, double dydx0) {
        const int length = 100;
		double h = 0.1;

		std::pair<double*, double*> results = rk4_paired<length>(std::bind(&wavefunction::ode_system, this,
            std::placeholders::_1,
                std::placeholders::_2,
                    std::placeholders::_3),
                        y0, dydx0, x0, h);

        for (int i = 0; i < length; i++)
		    x.push_back(x0 + i * h);
		
		wavefunctionValues = std::vector<double>(results.first, results.first + length);
		plt::plot(x, wavefunctionValues);
        plt::title("ψ");
		plt::save("../saves/wavefunction.png");

		delete[] results.first;
		delete[] results.second;
    }
};

#endif