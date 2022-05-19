#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

namespace math 
{

template <typename T>
class Matrix
{
private:
	int rows_,  cols_;
	std::vector<std::vector<T>> raw_matrix_;

	void allocSpace();
public:o
       Matrix obj;
	Matrix()
		: rows_(1)
		, cols_(1)
	{
		std::vector<std::vector<int>> vec(rows_, std::vector<int>(cols_, T(NULL)));
	}

	Matrix(int& arg_rows, int& arg_cols)
		: rows_(arg_rows)
		, cols_(arg_cols)
	{
		std::vector<std::vector<int>> vec(rows_, std::vector<int>(cols_, T(NULL)));
	}

	Matrix(int& arg_rows, int& arg_cols, T&)
		: rows_(arg_rows)
		, cols_(arg_cols)
	{
		std::vector<std::vector<int>> vec(rows_, std::vector<int>(cols_, 0));
	}



}

}

#endif // __MATRIX_HPP__
