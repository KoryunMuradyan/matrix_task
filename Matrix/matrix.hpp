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

Matrix::Matrix(const Matrix& m) 
	: rows_(m.rows_)
	, cols_(m.cols_)
{
	this->raw_matrix_ = m.raw_matrix_;
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if (this == &m) {
        return *this;
    }

    this->rows_ = m.rows_;
    this->cols_ = m.cols_;
    this->raw_matrix_ = m.raw_matrix_;
    return *this;
}


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

void Matrix::swapRows(int& r1, int& r2)
{
    std::vector<T> tmp_v = raw_matrix_[r1];
    raw_matrix_[r1] = raw_matrix_[r2];
    raw_matrix_[r2] = temp;
}

std::vector<T> Matrix::operator+(std::vector<T>& v1,  std::vector<T>& v2)
{
	std::transform (v1.begin(), v1.end(), v2.begin(), v1.begin(), std::plus<T>());
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] += m.p[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] -= m.p[i][j];
        }
    }
    return *this;
}


/*
void Matrix::allocSpace()
{
	p = new double*[rows_];
	for (int i = 0; i < rows_; ++i) {
		p[i] = new double[cols_];
	}
}
*/




#endif // __MATRIX_DEFINITION_HPP__
