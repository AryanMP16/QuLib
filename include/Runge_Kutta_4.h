#ifndef RUNGE_KATTA_4_H
#define RUNGE_KATTA_4_H
#include <functional>

using ODE_Function = std::function<std::pair<double, double>(double/*x*/, double/*y*/, double/*dydx*/)>;

template<int length> //"length" is the number of data points
std::pair<double*, double*> rk4_paired(ODE_Function fxn, double y0, double dydx0, double x0, double h) {

	double* y = new double[length];
	double* dydx = new double[length];
	
	y[0] = y0; //initialize output array
	dydx[0] = dydx0; //initialize output's associated derivatives array
	double x = x0; //initialize inputs array

	//main loop
	for (int n = 1; n < length; n++) {//y0 and dydx0 are already known, so we start from the second data point
		
		std::pair<double, double> k1 = fxn(x, y[n-1], dydx[n-1]);
		std::pair<double, double> k2 = fxn(x + h/2, y[n - 1] + h*k1.first/2, dydx[n - 1] + h*k1.second/2);
		std::pair<double, double> k3 = fxn(x + h/2, y[n - 1] + h*k2.first/2, dydx[n - 1] + h*k2.second/2);
		std::pair<double, double> k4 = fxn(x + h, y[n - 1] + h*k3.first, dydx[n - 1] + h*k3.second);

		y[n] = y[n-1] + h/6*(k1.first + 2*k2.first + 2*k3.first + k4.first);
		dydx[n] = dydx[n-1] + h/6*(k1.second + 2*k2.second + 2*k3.second + k4.second);

		x += h;
	}

	return std::make_pair(y, dydx);
}

#endif // !RUNGE_KATTA_4_H