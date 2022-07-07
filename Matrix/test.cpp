#include <iostream>
#include "matrix.hpp"

int main()
{
	//std::vector<std::vector<double> > init_vec = {{10, 1, 11, 27}, {9, 5, 3, 7}, {3, 7, 9, 8}};
	/*
	std::vector<std::vector<double> > init_vec = {
							{0, 5, 3, 7, 8},
							{10, 1, 11, 27, 17}, 
							{0, 0, 9, 8, 2}, 
							{0, 4, 0, 9, 3}
						};
						*/
	auto init_vec = MatrixRead<double>();
	math::Matrix<double> obj(init_vec);
	obj.gaussianEliminate();
	obj.print_vars();
	return 0;
}

