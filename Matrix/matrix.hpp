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

template <typename T>
Matrix<T>::Matrix(const Matrix& m) 
	: rows_(m.rows_)
	, cols_(m.cols_)
{
	this->raw_matrix_ = m.raw_matrix_;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& m)
{
    if (this == &m) {
        return *this;
    }

    this->rows_ = m.rows_;
    this->cols_ = m.cols_;
    this->raw_matrix_ = m.raw_matrix_;
    return *this;
}

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

template <typename T>
void Matrix<T>::swapRows(int& r1, int& r2)
{
    std::vector<T> temp = raw_matrix_[r1];
    raw_matrix_[r1] = raw_matrix_[r2];
    raw_matrix_[r2] = temp;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m)
{
	auto it_this = this->begin();
	std::for_each(m.begin(), m.end(),
			[&it_this](auto &i_m) {
				std::transform(
					it_this->begin(), it_this->end(), 
					i_m.begin(), it_this->begin(), 
					std::plus<T>()
				);
				it_this++;
			}
	);
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m)
{
	auto it_this = this->begin();
	std::for_each(m.begin(), m.end(),
			[&it_this](auto &i_m) {
				std::transform(
					it_this->begin(), it_this->end(), 
					i_m.begin(), it_this->begin(), 
					std::minus<T>()
				);
				it_this++;
			}
	);
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T Matrix<T>& m)
{
	/*// in this case an exception should be thrown (TO DO)
	if(this->cols_ != m.rows_) {
		throw
	}
	*/
	auto it_this = this->begin();

	std::for_each(this->begin(), this->end(), 
		
	)
	std::for_each(m.begin(), m.end(),
			[&it_this](auto &i_m) {
				std::transform(
					it_this->begin(), it_this->end(), 
					i_m.begin(), it_this->begin(), 
					std::minus<T>()
				);
				it_this++;
			}
	);
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T& arg_mult_num)
{
	std::for_each(this->begin(), this->end, 
		[](auto& i_vec) {
			std::transform(i_vec.begin(), i_vec.end(), i_vec.begin(), 
				[](T& num) -> T {
					return num * arg_mult_num; 
				}
			)
		}
	);
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(T& arg_mult_num)
{
	std::for_each(this->begin(), this->end, 
		[](auto& i_vec) {
			std::transform(i_vec.begin(), i_vec.end(), i_vec.begin(), 
				[](T& num) -> T {
					return num / arg_mult_num; 
				}
			)
		}
	);
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
