#include "matrix.h"
#include "complex.h"
#include "Runge_Kutta_4.h"
#include <iostream>
#include "matplotlibcpp.h"
#include "schrodingerSolver.h"
#include "integrate.h"

//ignore any squiggly lines under "matplotlibcpp.h". I swear it works just ignore it.

double U(double x){
	return 2 * x * x;
}

int main() {
	try {
		
		wavefunction psi(U);
		psi.solve(0, 1, 0);

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