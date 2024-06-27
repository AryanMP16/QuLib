#include "matrix.h"
#include "complex.h"
#include "Runge_Kutta_4.h"
#include <iostream>
#include "matplotlibcpp.h"
//ignore any squiggly lines under "matplotlibcpp.h". I swear it works just ignore it.

namespace plt = matplotlibcpp;

//Simple sinusoidal fxn
// std::pair<double, double> ode_system(double x, double y, double dydx) {
// 	double dyPrimedx = -y;
// 	return {dydx, dyPrimedx};
// }

std::pair<double, double> ode_system(double x, double y, double dydx) {
	double dyPrimedx = -y-x*x+3;
	return {dydx, dyPrimedx};
}

int main() {
	try {
		const int length = 100;
		double y0 = 1;
		double dydx0 = 0;
		double x0 = 0;
		double h = 0.1;

		std::pair<double*, double*> results = rk4_paired<length>(ode_system, y0, dydx0, x0, h);

		std::vector<double> x;
		for (int i = 0; i < length; ++i)
			x.push_back(x0 + i * h);
		
		std::vector<double> y(results.first, results.first + length);
		plt::plot(x, y);
		plt::save("../saves/output.png");

		delete[] results.first;
		delete[] results.second;

		return 0;

	//exception handling
	}	catch (const std::out_of_range& e) {
		std::cerr << "Out of Range error: " << e.what() << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Invalid Argument error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}