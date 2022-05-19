#ifndef __MATRIX_DEFINITION_HPP__
#define __MATRIX_DEFINITION_HPP__


using  namespace math;


Matrix::Matrix()
	: rows_(1)
	, cols_(1)
{
	std::vector<std::vector<int>> vec(rows_, std::vector<int>(cols_, T(NULL)));
}

Matrix::Matrix(int& arg_rows, int& arg_cols)
	: rows_(arg_rows)
	, cols_(arg_cols)
{
	std::vector<std::vector<int>> vec(rows_, std::vector<int>(cols_, T(NULL)));
}

Matrix::Matrix(int& arg_rows, int& arg_cols, T& arg_val)
	: rows_(arg_rows)
	, cols_(arg_cols)
{
	std::vector<std::vector<int>> vec(rows_, std::vector<int>(cols_, arg_val));
}

void Matrix::allocSpace()
{
	p = new double*[rows_];
	for (int i = 0; i < rows_; ++i) {
		p[i] = new double[cols_];
	}
}




#endif // __MATRIX_DEFINITION_HPP__
