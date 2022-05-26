#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <boost/range/algorithm_ext/for_each.hpp>

namespace math 
{

template <typename T>
class Matrix
{
private:
	int rows_,  cols_;
	std::vector<std::vector<T>> raw_matrix_;
	void allocSpace();
public:
	Matrix();
	Matrix(int&, int&);
	Matrix(int&, int&, T&);
	Matrix(std::vector<std::vector<T>>&);
	void swapRows(int&, int&);
	Matrix(const Matrix&);
	Matrix& operator=(const Matrix&);
	Matrix& operator*=(Matrix&);
        Matrix& operator*=(T&);
	Matrix& operator+=(const Matrix&);
        Matrix& operator/=(T&);
	Matrix<T>& operator-=(const Matrix<T>& m);
	std::vector<T> operator+(std::vector<T>&);
	Matrix transpose();
	static bool Not_Zero(T&);
        void gaussianEliminate();
        void gausHelper(std::vector<std::vector<T>>&);
        T find_GCD(T&, T&);
        T find_LCM(T&, T&);
        void print_matrix();
}; // class Matrix

} // namespace math

#endif // __MATRIX_HPP__
