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

double USimple(double x){
	return 0;
}

int main() {
	try {

		wavefunction psiQHO(U);
		psiQHO.solve(0, 1, 0);

		wavefunction psiPIB(USimple);
		psiPIB.solve(0, 0, 1);

		std::cout << "\n\nTesting: <ψ|p|ψ> for sin(x√2)\n";
		std::cout << psiPIB.expectation_value('p') << "  ~0" << std::endl;

		std::cout << "Testing: <ψ|p|ψ> for e^{(x^2)/2}\n";
		std::cout << psiQHO.expectation_value('p') << "  ~0" << std::endl;

		std::cout << "\n\n";

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