#include <iostream>
#include "ReadMatrix.hpp"
#include "matrix.hpp"

int main()
{
	auto arg = MatrixRead<int>();
	math::Matrix<int> obj(arg);
	obj.gaussianEliminate();
	obj.print_matrix();
	return 0;
}

