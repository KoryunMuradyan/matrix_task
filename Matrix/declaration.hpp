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
	void swapRows(int&, int&);
	Matrix(const Matrix&);
	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix&);
	
	Matrix transpose();
private:
<<<<<<< HEAD
=======
	std::vector<T> operator+(std::vector<T>&);
>>>>>>> d34cab864dbc92d834ab4722be95aa445bf99e3d

}; // class Matrix

} // namespace math

#endif // __MATRIX_HPP__
