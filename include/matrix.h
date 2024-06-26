#ifndef MATRIX_H
#define MATRIX_H
#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include <string>

template<class T>
class complexNumber; //forward declaration

//don't ask why these 2 need to be in this file. Just don't.
template<typename T>
struct is_complex_number : std::false_type {};

template<typename T>
struct is_complex_number<complexNumber<T>> : std::true_type {};

//matrix class
template<class T, int rows, int cols>
class matrix {
protected:
	T m_data[rows * cols];
	int m_rows;
	int m_cols;
public:
	//constructors
	matrix() : m_cols(cols), m_rows(rows) {
		for (int i = 0; i < rows * cols; i++)
			m_data[i] = T(); //default constructor of data type
	}

	matrix(const matrix& other) : m_cols(other.m_cols), m_rows(other.m_rows) {
		for (int i = 0; i < other.size(); i++)
			m_data[i] = other.m_data[i];
	}

	//getters and setters
	T& operator()(int y, int x) {
		if (y >= m_rows || x >= m_cols || y < 0 || x < 0)
			throw std::out_of_range("Index out of range!");
		return m_data[y * m_cols + x];
	}

	int get_rows() const {
		return m_rows;
	}

	int get_cols() const {
		return m_cols;
	}

	int size() const {
		return m_rows * m_cols;
	}

	void set(int y, int x, T value) {
		if (y >= m_rows || x >= m_cols || y < 0 || x < 0)
			throw std::out_of_range("Index out of range!");
		m_data[y * m_cols + x] = value;
	}

	//overloaded operators
	matrix operator+(const matrix& RHS) const {
		if (m_rows != RHS.m_rows || m_cols != RHS.m_cols)
			throw std::invalid_argument("Matrix dimensions must match for addition!");
		matrix toReturn(*this);
		for (int i = 0; i < m_rows * m_cols; i++)
			toReturn.m_data[i] += RHS.m_data[i];
		return toReturn;
	}

	template<int rightRows, int rightCols>
	matrix<T, rows, rightCols> operator*(matrix<T, rightRows, rightCols>& RHS) {
		if (cols != RHS.get_rows()) {
			throw std::invalid_argument("Matrix dimensions must match for multiplication!");
		}

		matrix<T, rows, rightCols> toReturn; //will, by default, start with zeros

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < rightCols; c++) {
				for (int k = 0; k < cols; k++) {
					toReturn(r, c) += (*this)(r, k) * RHS(k, c);
				}
			}
		}

		return toReturn;
	}

	matrix& operator=(const matrix& other) {
		if (this != &other) {
			if (m_rows != other.m_rows || m_cols != other.m_cols)
				throw std::invalid_argument("Matrix dimensions must match for addition!");
			for (int i = 0; i < other.size(); i++) {
				m_data[i] = other.m_data[i];
			}
		}
		return *this;
	}

	void displayMatrix() const {
		for (int i = 0; i < m_rows; i++) {
			std::cout << "| ";
			for (int j = 0; j < m_cols; j++) {
				if constexpr (is_complex_number<T>::value)
					m_data[i * m_cols + j].displayNumber();
				else
					std::cout << m_data[i * m_cols + j] << " ";
			}
			std::cout << "|\n";
		}
	}
};

template<class T, int rows>
class vector : public matrix<T, rows, 1> {
public:
	// Constructors
	vector() : matrix<T, rows, 1>() {}

	vector(const vector& other) : matrix<T, rows, 1>(other) {}

	vector(const matrix<T, rows, 1>& other) : matrix<T, rows, 1>(other) {}

	//getters, setters, and displayers
	T& operator()(int y) {
		if (y > this->m_rows || y < 0)
			throw std::out_of_range("Index out of range!");
		return this->m_data[y];
	}

	void set(int y, T value) {
		if (y > this->m_rows || y < 0)
			throw std::out_of_range("Index out of range!");
		this->m_data[y] = value;
	}

	void displayVector() const {
		for (int i = 0; i < this->m_rows; i++)
			std::cout << "| " << this->m_data[i] << " |\n";
	}
};

template<class T, int cols>
class covector : public matrix<T, 1, cols> {
public:
	// Constructors
	covector() : matrix<T, 1, cols>() {}

	covector(const covector& other) : matrix<T, 1, cols>(other) {}

	covector(const matrix<T, 1, cols>& other) : matrix<T, 1, cols>(other) {}

	//getters, setters, and displayers
	T& operator()(int x) {
		if (x > this->m_cols || x < 0)
			throw std::out_of_range("Index out of range!");
		return this->m_data[x];
	}

	void set(int x, T value) {
		if (x > this->m_cols || x < 0)
			throw std::out_of_range("Index out of range!");
		this->m_data[x] = value;
	}

	void displayVector() const {
		std::cout << "| ";
		for (int i = 0; i < this->m_cols; i++) {
			if constexpr (is_complex_number<T>::value)
				this->m_data[i].displayNumber();
			else
				std::cout << this->m_data[i] << " ";
		}
		std::cout << "|\n";
	}
};

template<class T, int cols>
covector<T, cols> dual(vector<T, cols>& v) {
	covector<T, cols> toReturn;
	for (int i = 0; i < cols; i++)
		toReturn.set(i, v(i));

	if constexpr (is_complex_number<T>::value) {
		for (int i = 0; i < cols; i++)
			toReturn(i).conj();
	}

	return toReturn;
}

#endif // !MATRIX_H
