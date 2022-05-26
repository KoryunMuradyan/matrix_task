#ifndef __MATRIX_DEFINITION_HPP__
#define __MATRIX_DEFINITION_HPP__

#include <functional>   // std::bind
#include "declaration.hpp"
#include <map>

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
Matrix<T> Matrix<T>::transpose()
{
	Matrix ret(cols_, rows_);
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			ret.raw_matrix_[j][i] = raw_matrix_[i][j];
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
	std::for_each(m.begin(), m.end(),[&it_this](auto &i_m) {
		std::transform(it_this->begin(), it_this->end(), 
			       i_m.begin(), it_this->begin(), 
			       std::plus<T>());
		it_this++;
	});
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m)
{
	auto it_this = this->begin();
	std::for_each(m.begin(), m.end(), [&it_this] (auto &i_m) {
		std::transform(it_this->begin(), it_this->end(), i_m.begin(),
			       it_this->begin(), std::minus<T>());
		it_this++;
	});
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(Matrix<T>& m)
{
	auto tmp_vec = m.transpose();
	std::for_each(this->begin(), this->end(), [&tmp_vec](auto& i_this_vec) { 
		std::vector<T> tmp_v_to_push;
		std::for_each(tmp_vec.begin(), tmp_vec.end(), 
			      [&i_this_vec, &tmp_v_to_push](auto& j_vec) {
			T num_to_pushback = T(NULL);
			boost::for_each(i_this_vec, j_vec, 
			[&num_to_pushback](T &a, T& b) { 
				num_to_pushback += (a*b);}
			);
			tmp_v_to_push.push_back(num_to_pushback);}
		);
		i_this_vec.swap(tmp_v_to_push);}
	);
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T& arg_mult_num)
{
	std::for_each(this->begin(), this->end, [&arg_mult_num] (auto& i_vec) {
		std::transform(i_vec.begin(), i_vec.end(), i_vec.begin(), 
			       [&arg_mult_num](T& num) -> T {
			return num * arg_mult_num;}
		);}
	);
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(T& arg_mult_num)
{
	std::for_each(this->begin(), this->end, 
	     	      [&arg_mult_num](auto& i_vec) {
		std::transform(i_vec.begin(), i_vec.end(), i_vec.begin(), 
			       [&arg_mult_num](T& num) -> T {
			return num / arg_mult_num; 
		});
	});
	return *this;
}

template <typename T>
bool Matrix<T>::Not_Zero(T& arg)
{
	return arg != 0 ;
}

template <typename T>
void Matrix<T>::gaussianEliminate()
{
	std::multimap<int, std::vector<T>> tmp_mltmap;
	int row_size = int(this->cols_ - 1);
	std::for_each(this->raw_matrix_.begin(), this->raw_matrix_.end(), 
		      [&row_size, &tmp_mltmap](std::vector<T> i) {
		auto zero_num = std::find_if(i.begin(), i.end(), Not_Zero);
		auto tmp = int(zero_num - i.begin());
		if (tmp == row_size) {
			tmp = -1;
		}
		tmp_mltmap.insert(std::pair<int, std::vector<int>>(tmp, i));
	});
	auto it = this->raw_matrix_.begin();
	std::for_each(tmp_mltmap.begin(), tmp_mltmap.end(), [&it](auto i) {
		*it++ == i.second;
	});
	//i.reverse();
}

// Gaus helper functions start
template <typename T>
void Matrix<T>::gausHelper(std::vector<std::vector<T>>& arg_vec)
{	
	auto it = arg_vec.begin() + 1;
	std::for_each(arg_vec.begin(), arg_vec.end(), [&arg_vec, &it](auto i) {
	        auto No_zero_num1 = std::find_if(i.begin(), i.end(), Not_Zero);
		auto No_zero_num2 = std::find_if(it->begin(), it->end(), Not_Zero);
		if(No_zero_num1 != *i - arg_vec.begin) { 
			if(No_zero_num1 == No_zero_num2) {
				auto mult = find_LCM(i[No_zero_num1], *(it + No_zero_num2));
				i *= mult/i[No_zero_num1];
				*it += mult/(*(it + No_zero_num2));
			}
		}
	});
}

template <typename T>
T Matrix<T>::find_GCD(T& arg_num_1, T& arg_num_2)
{
	if (arg_num_1 == arg_num_2) {
		return arg_num_1;
	}
	if (arg_num_1 > arg_num_2) {
		return gcd(arg_num_1-arg_num_2,arg_num_2);
	}
	return gcd(arg_num_1, arg_num_2-arg_num_1);
}

template <typename T>
T Matrix<T>::find_LCM(T& arg_num_1, T& arg_num_2)
{
	T gcd = find_GCD(arg_num_1, arg_num_2);
	return (arg_num_1*arg_num_2)/gcd; 
}

template <typename T>
void Matrix<T>::print_matrix()
{
	std::for_each(this->raw_matrix_.begin(), this->raw_matrix_.end(), 
			      [](auto& i){ std::for_each(i.begin(), i.end(), 
			      [](auto& j){ std::cout << j << " ";}
		);
		std::cout << std::endl;
	});
}

#endif // __MATRIX_DEFINITION_HPP__
