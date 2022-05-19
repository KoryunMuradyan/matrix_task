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
public:
	Matrix();
	Matrix(int&, int&);
	Matrix(int&, int&, T&);
	Matrix(std::vector<std::vector<T>>&);
	Matrix(const Matrix&);
	Matrix& operator=(const Matrix&);
	
	Matrix transpose();

}

}

#endif // __MATRIX_HPP__
