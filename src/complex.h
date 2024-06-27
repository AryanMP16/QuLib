#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>

template<class T>
class complexNumber {
private:
	T real;
	T imaginary;
public:
	complexNumber(T r, T i) : real(r), imaginary(i) {}
	complexNumber() : real(T()), imaginary(T()) {}
	complexNumber(const complexNumber& other) : real(other.real), imaginary(other.imaginary) {}

	complexNumber& operator=(const complexNumber& other) {
		if (this != &other) {
			real = other.real;
			imaginary = other.imaginary;
		}
		return *this;
	}

	complexNumber operator+(const complexNumber& other) const {
		return complexNumber(real + other.real, imaginary + other.imaginary);
	}

	complexNumber& operator+=(const complexNumber& other) {
		real += other.real;
		imaginary += other.imaginary;
		return *this;
	}

	complexNumber operator*(complexNumber& other) {
		return complexNumber(
			(real * other.real) - (imaginary * other.imaginary),
			(real * other.imaginary) + (imaginary * other.real)
		);
	}

	void conj() {
		imaginary = -imaginary;
	}

	void displayNumber() const {
		if (real == 0 && imaginary == 0) {
			std::cout << "0\t";
			return;
		}
		if (real == 0) {
			std::cout << imaginary << "i\t";
			return;
		}
		if (imaginary == 0) {
			std::cout << real << "\t";
			return;
		}
		if (imaginary < 0) {
			std::cout << real << "-" << -imaginary << "i\t";
			return;
		}

		std::cout << real << "+" << imaginary << "i\t";
	}
};

#endif // !COMPLEX_H