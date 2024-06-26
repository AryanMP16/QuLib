#include "matrix.h"
#include "complex.h"
#include "Runge_Kutta_4.h"
#include <iostream>

std::pair<double, double> ode_system(double x, double y, double dydx) {
	double dyPrimedx = -y;
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

		for (int i = 0; i < length; ++i) {
			std::cout << x0 + i * h << std::endl;
		}

		std::cout << "//\n//\n//\n//\n//\n//\nFUNCTION Y:\n";

		for (int i = 0; i < length; ++i) {
			std::cout << results.first[i] << std::endl;
		}

		/*std::cout << "//\n//\n//\n//\n//\n//\n";

		for (int i = 0; i < length; ++i) {
			std::cout << results.second[i] << std::endl;
		}*/

		delete[] results.first;
		delete[] results.second;

		//matrix.h and complex.h test cases (all passed)

  //      matrix<complexNumber<int>, 3, 3> m1;
		//matrix<complexNumber<int>, 3, 3> m2;

		//m1.set(0, 0, complexNumber<int>(0, 1));
		//m1.set(0, 1, complexNumber<int>(4, 1));
		//m1.set(0, 2, complexNumber<int>(2, 2));

		//m1.set(1, 0, complexNumber<int>(0, 0));
		//m1.set(1, 1, complexNumber<int>(9, 1));
		//m1.set(1, 2, complexNumber<int>(1, 0));

		//m1.set(2, 0, complexNumber<int>(5, 5));
		//m1.set(2, 1, complexNumber<int>(0, 0));
		//m1.set(2, 2, complexNumber<int>(3, 0));

		////

		//m2.set(0, 0, complexNumber<int>(4, 0));
		//m2.set(0, 1, complexNumber<int>(2, 1));
		//m2.set(0, 2, complexNumber<int>(0, 0));

		//m2.set(1, 0, complexNumber<int>(0, 9));
		//m2.set(1, 1, complexNumber<int>(0, 1));
		//m2.set(1, 2, complexNumber<int>(8, 1));

		//m2.set(2, 0, complexNumber<int>(1, 1));
		//m2.set(2, 1, complexNumber<int>(6, 3));
		//m2.set(2, 2, complexNumber<int>(3, 5));

		//std::cout << "Complex matrix multiplication:\n";
		//std::cout << "Matrix 1:\n";
		//m1.displayMatrix();
		//std::cout << "Matrix 2:\n";
		//m2.displayMatrix();
		//std::cout << "Result:\n";
		//matrix<complexNumber<int>, 3, 3>m3 = m1 * m2;
		//m3.displayMatrix();

		//std::cout << "Complex conjugation testing:\n";
		//for (int i = 0; i < m3.get_rows(); i++) {
		//	for (int j = 0; j < m3.get_cols(); j++)
		//		m3(i, j).conj();
		//}
		//m3.displayMatrix();

		//std::cout << "Hermitian conjugation testing:\n";
		//vector<complexNumber<int>, 4> v1;
		//v1.set(0, complexNumber<int>(1, 1));
		//v1.set(1, complexNumber<int>(1, 0));
		//v1.set(2, complexNumber<int>(0, 1));
		//v1.set(3, complexNumber<int>(0, 0));
		//dual(v1).displayVector();

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