#include <iostream>
#include "ReadMatrix.hpp"
#include "matrix.hpp"

int main()
{
	//std::vector<std::vector<int> > init_vec = {{10, 1, 11, 27}, {9, 5, 3, 7}, {3, 7, 9, 8}, {4, 5, 6, 9}};
	std::vector<std::vector<double> > init_vec = {
							{0, 5, 3, 7, 8},
							{10, 1, 11, 27, 17}, 
							{0, 0, 9, 8, 2}, 
							{0, 4, 0, 9, 3}
						};
	math::Matrix<double> obj(init_vec);
	obj.gaussianEliminate();
	//obj.print_matrix();
	obj.print_vars();
	/*
	//auto arg = MatrixRead<int>();
	//math::Matrix<int> obj(arg);
	obj.print_matrix();
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	//obj.print_matrix();
	//obj.gaussianEliminate();
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	*/
	//std::string var1 = "x" + std::to_string(2);
	//std::cout << var1 << std::endl;
	return 0;
}

