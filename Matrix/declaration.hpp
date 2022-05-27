#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <boost/range/algorithm_ext/for_each.hpp>

namespace math 
{

template <typename T>
class Matrix
{
private:
	std::map<std::string, T> _variables;
	int rows_,  cols_;
	std::vector<std::vector<T>> raw_matrix_;
	void allocSpace();
	void swapRows(int&, int&);
	std::vector<std::vector<T>> find_unknown_vars_by_known();             
	void sort_rows_with_zero();                                           
public:
	Matrix();
	Matrix(int&, int&);
	Matrix(int&, int&, T&);
	Matrix(std::vector<std::vector<T>>&);
	Matrix(const Matrix&);
	Matrix& operator=(const Matrix&);
	Matrix& operator*=(Matrix&);
        Matrix& operator*=(T&);
	Matrix& operator+=(const Matrix&);
        Matrix& operator/=(T&);
        void gaussianEliminate();
	void gausHelper(std::vector<std::vector<T>>&);
	void defineVariables(std::vector<std::vector<T>>&);
	static bool Not_Zero(T&);
        void print_matrix();
	Matrix transpose();
	std::vector<T> operator+(std::vector<T>&);
	Matrix<T>& operator-=(const Matrix<T>& m);
	void print_vars();
private:
	static T find_GCD(T, T);
	static T find_LCM(const T&, const T&);
}; // class Matrix

} // namespace math

#endif // __MATRIX_HPP__
