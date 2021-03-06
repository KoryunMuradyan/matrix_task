#ifndef __MATRIX_DEFINITION_HPP__
#define __MATRIX_DEFINITION_HPP__

#include <numeric>
#include <map>
#include <cstdlib>
#include <iterator>
#include "declaration.hpp"

using  namespace math;


template <typename T>
Matrix<T>::Matrix()
	: rows_(1)
	, cols_(1)
{
	matrix_type<T> vec(rows_, vec_type<T>(cols_, int(NULL)));
}

template <typename T>
Matrix<T>::Matrix(int& arg_rows, int& arg_cols)
	: rows_(arg_rows)
	, cols_(arg_cols)
{
	matrix_type<T> raw_matrix_(rows_, 
					vec_type<T>(cols_, T(NULL)));
}

template <typename T>
Matrix<T>::Matrix(int& arg_rows, int& arg_cols, T& arg_val)
	: rows_(arg_rows)
	, cols_(arg_cols)
{
	matrix_type<T> raw_matrix_(rows_,
                                    vec_type<T>(cols_, arg_val));
}

template <typename T>
Matrix<T>::Matrix(matrix_type<T>& arg_vec) 
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
	vec_type<T> temp = raw_matrix_[r1];
	raw_matrix_[r1] = raw_matrix_[r2];
	raw_matrix_[r2] = temp;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m)
{
	auto it_this = this->begin();
	for_each(m.begin(), m.end(),[&it_this](auto &i_m) {
		transform(it_this->begin(), it_this->end(), 
			       i_m.begin(), it_this->begin(), 
			       plus<T>());
		it_this++;
	});
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m)
{
	auto it_this = this->begin();
	for_each(m.begin(), m.end(), [&it_this] (auto &i_m) {
		transform(it_this->begin(), it_this->end(), i_m.begin(),
			       it_this->begin(), minus<T>());
		it_this++;
	});
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(Matrix<T>& m)
{
	auto tmp_vec = m.transpose();
	for_each(this->begin(), this->end(),
                      [&tmp_vec](auto& i_this_vec) { 
		vec_type<T> tmp_v_to_push;
		for_each(tmp_vec.begin(), tmp_vec.end(), 
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
       for_each(this->begin(), this->end, [&arg_mult_num] (auto& i_vec) {
		transform(i_vec.begin(), i_vec.end(), i_vec.begin(), 
			       [&arg_mult_num](T& num) -> T {
			return num * arg_mult_num;}
		);}
	);
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(T& arg_mult_num)
{
	for_each(this->begin(), this->end, 
	     	      [&arg_mult_num](auto& i_vec) {
		transform(i_vec.begin(), i_vec.end(), i_vec.begin(), 
			       [&arg_mult_num](T& num) -> T {
			return num / arg_mult_num; 
		});
	});
	return *this;
}

template <typename T>
void Matrix<T>::sort_rows_with_zero()
{
	multimap<int, vec_type<T>> tmp_mltmap;
	int row_size = int(this->cols_ - 1);
	for_each(this->raw_matrix_.begin(), this->raw_matrix_.end(), 
			[&row_size, &tmp_mltmap](vec_type<T> i) {
			auto front_zero_num = find_if(i.begin(), i.end(), 
					Not_Zero
					);
			int pos = int(front_zero_num - i.begin());
			if (pos == row_size) {
			pos = -1;
			}
			tmp_mltmap.insert(pair<int, vec_type<T>>(pos, i));

			}
		     );
	auto it = this->raw_matrix_.begin();
	for_each(tmp_mltmap.begin(), tmp_mltmap.end(), 
			[&it](auto i) {
			*it++ = i.second;
			}
		     );
}

template <typename T>
void Matrix<T>::define_each_X(std::vector<T>& row, int&& pos)
{
	string str = "x" + std::to_string(pos + 1);
	auto ptr_vars = &_variables;
	auto tmp_num = accumulate(row.begin() + pos + 1, row.end() - 1, T(NULL));
	row[pos] = (row.back()-tmp_num)/(row[pos]);
	ptr_vars->insert(pair<std::string, T>(str, row[pos]));
}

template <typename T>
void Matrix<T>::put_known_vars(typename std::vector<std::vector<T>>::iterator& begin, 
		typename matrix_type<T>::iterator& end, int& pos, T& var)
{
	auto a = begin;
	for_each(begin, end, [&](auto& row) {
				row[pos] *= var;
			}
		);
}

template <typename T>
void Matrix<T>::defineVariables()
{
	auto arg_vec = raw_matrix_;
	*(arg_vec[0].end() - 2) = arg_vec[0].back()/(*(arg_vec[0].end() - 2));
	_variables.insert(pair<std::string, T>("x0", *(arg_vec[0].end() - 2)));
	auto ptr_vars = &_variables;
	auto it_begin = arg_vec.begin() + 1;
	auto it_end = arg_vec.end();
	for_each(arg_vec.begin(), arg_vec.end() - 1, [&](auto& row) {
				auto front_not_zero_num = find_if(row.begin(), row.end(), Not_Zero);
				int pos = int(front_not_zero_num - row.begin());
				put_known_vars(it_begin, it_end, pos, row[pos]);
				define_each_X(*it_begin, std::move(pos - 1));
				it_begin++;
			}
	);
}

template <typename T>
void Matrix<T>::gaussianEliminate()
{	
	sort_rows_with_zero();
	reverse(raw_matrix_.begin(), raw_matrix_.end());
	gausHelper(raw_matrix_);	
	defineVariables();
}


template <typename T>
void Matrix<T>::gausHelper(matrix_type<T>& arg_vec)
{	
	auto it = arg_vec.begin();
	for_each(arg_vec.begin(), arg_vec.end() - 1, [&](auto& i) {
		it++;
		auto No_zero_num1 = find_if(i.begin(), i.end(), Not_Zero);
		auto No_zero_num2 = find_if(it->begin(), it->end(), Not_Zero);
		int pos1 = int(No_zero_num1 - i.begin());
		int pos2 = int(No_zero_num2 - it->begin());
		vec_type<T> tmp_v = *it;
		if (pos1 != int(i.size())) { 
			if (pos1 == pos2) {
				T mult = find_LCM(abs(i[pos1]),
						  abs(tmp_v[pos1]));
				T mult_i = mult / i[pos1];
				T mult_it = mult/tmp_v[pos1];
				transform(i.begin(), i.end(), i.begin(),
					  bind1st(std::multiplies<T>(),
						   mult_i));
				transform(it->begin(), it->end(),
					  tmp_v.begin(),
				bind1st(std::multiplies<T>(), mult_it));
				if (mult_i*i[pos1] == -(mult_it*tmp_v[pos1])) {
					transform(i.begin(), i.end(),
						  tmp_v.begin(), 
						  i.begin(),
					plus<T>());
				} else {
					transform(i.begin(), i.end(),
						  tmp_v.begin(), i.begin(), 
						  minus<T>());
				}
			}	
		}

		} );
	if (*((arg_vec.begin())->end() - 3) != 0) {
		gausHelper(arg_vec);
	} else {
		return;
	}
}

template <typename T>
T Matrix<T>::find_GCD(T arg_num_1, T arg_num_2)
{
	if (arg_num_1 == arg_num_2) {
		return arg_num_1;
	if (arg_num_1 > arg_num_2)
		return find_GCD(arg_num_1-arg_num_2,arg_num_2);
	return find_GCD(arg_num_1, arg_num_2-arg_num_1);
	}
	if (arg_num_1 > arg_num_2) {
		return find_GCD(arg_num_1-arg_num_2,arg_num_2);
	}
	return find_GCD(arg_num_1, arg_num_2-arg_num_1);
}

template <typename T>
T Matrix<T>::find_LCM(const T& arg_num_1, const T& arg_num_2)
{
	T gcd = find_GCD(arg_num_1, arg_num_2);
	return (arg_num_1*arg_num_2)/gcd; 
}

template <typename T>
bool Matrix<T>::Not_Zero(T& arg)
{
	return arg != T(NULL);
}

// Gaus helper functions end

template <typename T>
void Matrix<T>::print_matrix()
{
	for_each(this->raw_matrix_.begin(), this->raw_matrix_.end(), 
			      [](auto& i){ for_each(i.begin(), i.end(), 
			      [](auto& j){ cout << j << " ";}
		);
		cout << std::endl;
	});
}

template <typename T>
void Matrix<T>::print_vars()
{
	for(auto i: _variables) {
		cout  <<  i.first << "  " << i.second << std::endl;
	}
}

#endif // __MATRIX_DEFINITION_HPP__
