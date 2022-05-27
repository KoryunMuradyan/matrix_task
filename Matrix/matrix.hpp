#ifndef __MATRIX_DEFINITION_HPP__
#define __MATRIX_DEFINITION_HPP__

#include <numeric>
#include <map>
#include <cstdlib>
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
	std::vector<std::vector<T>> raw_matrix_(rows_, std::vector<T>(cols_, T(NULL)));
}

template <typename T>
Matrix<T>::Matrix(int& arg_rows, int& arg_cols, T& arg_val)
	: rows_(arg_rows)
	, cols_(arg_cols)
{
	std::vector<std::vector<T>> raw_matrix_(rows_, std::vector<T>(cols_, arg_val));
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>>& arg_vec) 
	: raw_matrix_(arg_vec)
{
	this->cols_ = int(arg_vec[1].size());
	this->cols_ = int(arg_vec.size());
}

template <typename T>
Matrix<T>::Matrix(const Matrix& m) 
	: rows_(m.rows_)
	, cols_(m.cols_)
{
	this->raw_matrix_ = m.raw_matrix_;
	this->_variables = m._variables;
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
void Matrix<T>::gaussianEliminate()
{
	std::multimap<int, std::vector<T>> tmp_mltmap;
	int row_size = int(this->cols_ - 1);
	std::for_each(this->raw_matrix_.begin(), this->raw_matrix_.end(), 
<<<<<<< HEAD
		[&row_size, &tmp_mltmap](std::vector<T> i) {
			auto front_zero_num = std::find_if(i.begin(), i.end(), 
				Not_Zero
			);
			int pos = int(front_zero_num - i.begin());
			if (pos == row_size) {
				pos = -1;
			}
			tmp_mltmap.insert(std::pair<int, std::vector<T>>(pos, i));
=======
		      [&row_size, &tmp_mltmap](std::vector<T> i) {
		auto zero_num = std::find_if(i.begin(), i.end(), Not_Zero);
		auto tmp = int(zero_num - i.begin());
		if (tmp == row_size) {
			tmp = -1;
>>>>>>> eb93928bebd5b3ed595edd7f76ffd34c55bee23d
		}
		tmp_mltmap.insert(std::pair<int, std::vector<int>>(tmp, i));
	});
	auto it = this->raw_matrix_.begin();
<<<<<<< HEAD
	std::for_each(tmp_mltmap.begin(), tmp_mltmap.end(), 
			[&it](auto i) {
				*it++ = i.second;
			}
	);
	std::reverse(raw_matrix_.begin(), raw_matrix_.end());
	this->gausHelper(this->raw_matrix_);	

	auto tmp_vec = this->raw_matrix_;
	*(tmp_vec[0].rbegin() + 1) = *(tmp_vec[0].rbegin())/(*(tmp_vec[0].rbegin() + 1));
	it = tmp_vec.begin();
	auto vars = _variables;
	std::for_each(tmp_vec.begin() + 1, tmp_vec.end(), 
		[&vars, &it](auto& i){
			auto it2 = it->begin();
			std::transform(i.begin(), i.end() - 1, i.begin(), 
				[&it2](auto& i2)->T{
					if(*it2 != T(NULL)) {
						i2 *= *it2;
					}
					it2++;
					return i2; 
				}
			);
			it++;
		}
	);
	std::string str_tmp = "x" + std::to_string(cols_);
	_variables.insert(std::pair<std::string, T>(str_tmp, T(*(tmp_vec[0].rbegin() + 1))));
	defineVariables(tmp_vec);
}

template <typename T>
void Matrix<T>::defineVariables(std::vector<std::vector<T>>& arg_vec)
{
	auto ptr_vars = &_variables;
	std::for_each(arg_vec.begin() + 1, arg_vec.end(), 
		[&ptr_vars](std::vector<T> i) {
			auto front_not_zero_num = std::find_if(i.begin(), i.end(), 
							Not_Zero
						);
			int pos = int(front_not_zero_num - i.begin());
			auto tmp_num = std::accumulate(front_not_zero_num + 1, 
						i.end() - 1, T(NULL)
					);
			tmp_num = (i.back()-tmp_num)/(*front_not_zero_num);
			std::string str = "x" + std::to_string(pos + 1);
			ptr_vars->insert(std::pair<std::string, T>(str, tmp_num));
		}
	);
}

=======
	std::for_each(tmp_mltmap.begin(), tmp_mltmap.end(), [&it](auto i) {
		*it++ == i.second;
	});
	//i.reverse();
}

>>>>>>> eb93928bebd5b3ed595edd7f76ffd34c55bee23d
// Gaus helper functions start
template <typename T>
void Matrix<T>::gausHelper(std::vector<std::vector<T>>& arg_vec)
{	
<<<<<<< HEAD
	auto it = arg_vec.begin();
	std::for_each(arg_vec.begin(), arg_vec.end() - 1, 
		[&arg_vec, &it](auto& i){
			it++;
			auto No_zero_num1 = std::find_if(i.begin(), i.end(), 
					Not_Zero
			);
			auto No_zero_num2 = std::find_if(it->begin(), it->end(), 
					Not_Zero
			);
			int pos1 = int(No_zero_num1 - i.begin());
			int pos2 = int(No_zero_num2 - it->begin());
			if(pos1 != int(i.size())){ 
				if(pos1 == pos2) {
					std::vector<T> tmp_v = *it;
					T mult = find_LCM(abs(i[pos1]), abs(tmp_v[pos1]));
					T mult_i = mult/i[pos1];
					T mult_it = mult/tmp_v[pos1];
					std::transform(i.begin(), i.end(), i.begin(),
						std::bind1st(std::multiplies<T>(), mult_i));
					std::transform(it->begin(), it->end(), tmp_v.begin(),
						std::bind1st(std::multiplies<T>(), mult_it));
					if(mult_i*i[pos1] == -(mult_it*tmp_v[pos1])) {
						std::transform(i.begin(), i.end(), tmp_v.begin(), i.begin(), std::plus<T>());
					} else {
						std::transform(i.begin(), i.end(), tmp_v.begin(), i.begin(), std::minus<T>());
					}
				}
			}
		}
	);
	if(*((arg_vec.begin())->end() - 3) != 0) {
		gausHelper(arg_vec);
	} else {
		return;
	}
=======
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
>>>>>>> eb93928bebd5b3ed595edd7f76ffd34c55bee23d
}

template <typename T>
T Matrix<T>::find_GCD(T arg_num_1, T arg_num_2)
{
	if (arg_num_1 == arg_num_2) {
		return arg_num_1;
<<<<<<< HEAD
	if (arg_num_1 > arg_num_2)
		return find_GCD(arg_num_1-arg_num_2,arg_num_2);
	return find_GCD(arg_num_1, arg_num_2-arg_num_1);
=======
	}
	if (arg_num_1 > arg_num_2) {
		return gcd(arg_num_1-arg_num_2,arg_num_2);
	}
	return gcd(arg_num_1, arg_num_2-arg_num_1);
>>>>>>> eb93928bebd5b3ed595edd7f76ffd34c55bee23d
}

template <typename T>
T Matrix<T>::find_LCM(const T& arg_num_1, const T& arg_num_2)
{
	T gcd = find_GCD(arg_num_1, arg_num_2);
	return (arg_num_1*arg_num_2)/gcd; 
}

<<<<<<< HEAD
template <typename T>
bool Matrix<T>::Not_Zero(T& arg)
{
	return arg != T(NULL);
}

// Gaus helper functions end

=======
>>>>>>> eb93928bebd5b3ed595edd7f76ffd34c55bee23d
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

template <typename T>
void Matrix<T>::print_vars()
{
	for(auto i: _variables) {
		std::cout  <<  i.first << "  " << i.second << std::endl;
	}
}

#endif // __MATRIX_DEFINITION_HPP__
