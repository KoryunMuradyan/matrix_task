#ifndef __MATRIX_DEFINITION_HPP__
#define __MATRIX_DEFINITION_HPP__

#include "declaration.hpp"

using  namespace math;

template <typename T>
Matrix<T>::Matrix()
	: rows_(1)
	, cols_(1)
{
	std::vector<std::vector<T>> vec(rows_, std::vector<T>(cols_, T(NULL)));
}

template <typename T>
Matrix<T>::Matrix(int& arg_rows, int& arg_cols)
	: rows_(arg_rows)
	, cols_(arg_cols)
{
	std::vector<std::vector<T>> vec(rows_, std::vector<T>(cols_, T(NULL)));
}

template <typename T>
Matrix<T>::Matrix(int& arg_rows, int& arg_cols, T& arg_val)
	: rows_(arg_rows)
	, cols_(arg_cols)
{
	std::vector<std::vector<T>> vec(rows_, std::vector<T>(cols_, arg_val));
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>>& arg_vec) 
	: raw_matrix_(arg_vec)
{

}

<<<<<<< HEAD
Matrix::Matrix(const Matrix& m) 
=======
//<<<<<<< HEAD
template <typename T>
Matrix<T>::Matrix(const Matrix& m) 
>>>>>>> d34cab864dbc92d834ab4722be95aa445bf99e3d
	: rows_(m.rows_)
	, cols_(m.cols_)
{
	this->raw_matrix_ = m.raw_matrix_;
}

template <typename T>
<<<<<<< HEAD
Matrix& Matrix::operator=(const Matrix& m)
=======
Matrix<T>& Matrix<T>::operator=(const Matrix& m)
>>>>>>> d34cab864dbc92d834ab4722be95aa445bf99e3d
{
    if (this == &m) {
        return *this;
    }

    this->rows_ = m.rows_;
    this->cols_ = m.cols_;
    this->raw_matrix_ = m.raw_matrix_;
    return *this;
}

<<<<<<< HEAD

template <typename T>
Matrix Matrix::transpone()
{
	Matrix ret(cols_, rows_);
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			ret.p[j][i] = p[i][j];
		}
	}
	return ret;
}

=======
//template <typename T>
//Matrix<T> Matrix<T>::transpose()
//{
//	Matrix ret(cols_, rows_);
//	for (int i = 0; i < rows_; ++i) {
//		for (int j = 0; j < cols_; ++j) {
//			ret.p[j][i] = p[i][j];
//		}
//	}
//	return ret;
//}
//=======
>>>>>>> d34cab864dbc92d834ab4722be95aa445bf99e3d
//template <typename T>
//Matrix<T> Matrix<T>::transpose()
//{
//	Matrix<T> ret(cols_, rows_);
//	for (int i = 0; i < rows_; ++i) {
//		for (int j = 0; j < cols_; ++j) {
//			ret.p[j][i] = p[i][j];
//		}
//	}
//	return ret;
//}

template <typename T>
void Matrix<T>::swapRows(int& r1, int& r2)
{
    std::vector<T> temp = raw_matrix_[r1];
    raw_matrix_[r1] = raw_matrix_[r2];
    raw_matrix_[r2] = temp;
}

template <typename T>
<<<<<<< HEAD
std::vector<T> Matrix::operator+(std::vector<T>& v1,  std::vector<T>& v2)
=======
std::vector<T> Matrix<T>::operator+(std::vector<T>& v2)
>>>>>>> d34cab864dbc92d834ab4722be95aa445bf99e3d
{
	std::transform (this->begin(), this->end(), v2.begin(), this->begin(), std::plus<T>());
	return *this;
}

template <typename T>
<<<<<<< HEAD
Matrix& Matrix::operator+=(const Matrix& m)
=======
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m)
>>>>>>> d34cab864dbc92d834ab4722be95aa445bf99e3d
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            m[i][j] += m.p[i][j];
        }
    }
    return *this;
}

template <typename T>
<<<<<<< HEAD
Matrix& Matrix::operator-=(const Matrix& m)
=======
Matrix<T>& Matrix<T>::operator-=(const Matrix& m)
>>>>>>> d34cab864dbc92d834ab4722be95aa445bf99e3d
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] -= m.p[i][j];
        }
    }
    return *this;
}


/*
void Matrix<T>::allocSpace()
{
	p = new double*[rows_];
	for (int i = 0; i < rows_; ++i) {
		p[i] = new double[cols_];
	}
}
*/

#endif // __MATRIX_DEFINITION_HPP__
