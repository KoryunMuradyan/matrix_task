#ifndef __MATRIX_DEFINITION_HPP__
#define __MATRIX_DEFINITION_HPP__


using  namespace math;

Matrix::Matrix()
	: rows_(1)
	, cols_(1)
{
	std::vector<std::vector<T>> vec(rows_, std::vector<T>(cols_, T(NULL)));
}

Matrix::Matrix(int& arg_rows, int& arg_cols)
	: rows_(arg_rows)
	, cols_(arg_cols)
{
	std::vector<std::vector<T>> vec(rows_, std::vector<T>(cols_, T(NULL)));
}

Matrix::Matrix(int& arg_rows, int& arg_cols, T& arg_val)
	: rows_(arg_rows)
	, cols_(arg_cols)
{
	std::vector<std::vector<T>> vec(rows_, std::vector<T>(cols_, arg_val));
}

Matrix::Matrix(std::vector<std::vector<T>>& arg_vec) 
	: raw_matrix_(arg_vec)
{

}

Matrix Matrix::transpone()
{
	for_each(this->raw_matrix_.begin(), this->end(), 
			for_each())
    Matrix ret(cols_, rows_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            ret.p[j][i] = p[i][j];
        }
    }
    return ret;
}


void Matrix::allocSpace()
{
	p = new double*[rows_];
	for (int i = 0; i < rows_; ++i) {
		p[i] = new double[cols_];
	}
}




#endif // __MATRIX_DEFINITION_HPP__
