#include <iostream>
#include "ReadMatrix.hpp"
#include "matrix.hpp"

int main()
{
	std::vector<std::vector<int> > init_vec = {{10, 1, 11, 27}, {9, 5, 3, 7}, {3, 7, 9, 8}, {4, 5, 6, 9}};
	//auto arg = MatrixRead<int>();
	//math::Matrix<int> obj(arg);
	math::Matrix<int> obj(init_vec);
	obj.gaussianEliminate();
	//obj.print_matrix();
	return 0;
}

