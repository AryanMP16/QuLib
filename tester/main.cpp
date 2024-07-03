#include "matrix.h"
#include "complex.h"
#include "Runge_Kutta_4.h"
#include <iostream>
#include "matplotlibcpp.h"
#include "schrodingerSolver.h"
#include "integrate.h"
#include <cassert>

//ignore any squiggly lines under "matplotlibcpp.h". I swear it works just ignore it.

double U1(double x){return 0;} //Particle in box
double U2(double x){return 2 * x * x;} //Quantum harmonic oscillator
double U3(double x){return x*x*x;} //cubic
double U4(double x){return std::cos(x);} //cos
double U5(double x){return std::sin(x);} //sin
double U6(double x){return std::tan(x);} //tan
double U7(double x){return std::log(x);} //log
double U8(double x){return std::exp(x);} //e^x
double U9(double x){return 1/x;} //reciprocal
double U10(double x){return x;} //linear

void testODESolver_DEV_ONLY(){
	wavefunction psi_functions[10] = {
		wavefunction(U1),
		wavefunction(U2),
		wavefunction(U3),
		wavefunction(U4),
		wavefunction(U5),
		wavefunction(U6),
		wavefunction(U7),
		wavefunction(U8),
		wavefunction(U9),
		wavefunction(U10)
	};

	int initialConditions[10][3] = { //x0, y0, dydx0
		{0, 0, 1}, //particle in a box
		{0, 1, 0}, //QHO
		{0, 0, 1}, //cubic
		{0, 0, 1}, //cos
		{0, 0, 1}, //sin
		{0, 0, 1}, //tan --> discontinuities result in strange behaviour after pi/2
		{1, 0, 1}, //log
		{0, 0, 1}, //exponential
		{1, 0, 1}, //reciprocal
		{0, 0, 1} //linear
	};

	for (int i = 0; i < 10; i++) {
		psi_functions[i].solve(initialConditions[i][0],
								initialConditions[i][1],
								initialConditions[i][2], std::to_string(i));
		//At this stage, I will manually check each graph against wolfram alpha to ensure validity
	}
}

int main() {
	try {
		
		testODESolver_DEV_ONLY();
		
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