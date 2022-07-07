#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <boost/range/algorithm_ext/for_each.hpp>
#include "ReadMatrix.hpp"

#include <iterator>
#include <vector>

using namespace std;
template <typename T>
using vec_type = std::vector<T>; 
template <typename T>
using matrix_type = std::vector<std::vector<T>>;

namespace math 
{

template <typename T>
class Matrix
{
	private:
		std::map<std::string, T> _variables;
		int rows_,  cols_;
		matrix_type<T> raw_matrix_;
		void allocSpace();
		void swapRows(int&, int&);
		matrix_type<T> find_unknown_vars_by_known();
		void define_each_X(std::vector<T>&, int&&);
		void put_known_vars(typename std::vector<std::vector<T>>::iterator&,
                                    typename std::vector<std::vector<T>>::iterator&i,
                                    int&, T&);
		void sort_rows_with_zero();                                           
		void gausHelper(matrix_type<T>&);
		static T find_GCD(T, T);
		static T find_LCM(const T&, const T&);
		Matrix transpose();
		void defineVariables();
		static bool Not_Zero(T&);
	public:
		Matrix();
		Matrix(int&, int&);
		Matrix(int&, int&, T&);
		Matrix(matrix_type<T>&);
		Matrix(const Matrix&);
		Matrix& operator=(const Matrix&);
		Matrix& operator*=(Matrix&);
		Matrix& operator*=(T&);
		Matrix& operator+=(const Matrix&);
		Matrix& operator/=(T&);
		vec_type<T> operator+(vec_type<T>&);
		Matrix<T>& operator-=(const Matrix<T>& m);
		void gaussianEliminate();
		void print_matrix();
		void print_vars();
}; // class Matrix

} // namespace math

#endif // __MATRIX_HPP__
