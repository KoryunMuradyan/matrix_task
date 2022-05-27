#ifndef READ_FROM_FILE
#define READ_FROM_FILE

#include <algorithm>
#include <sstream>
#include <fstream>
#include <iterator>     // back_inserter
#include <vector>
#include <iostream>

template <typename T>
void NumLinetoIntVec(std::vector<std::vector<T>>& arg_vec, 
		     std::string& arg_str) 
{
	std::istringstream iss(arg_str);
	std::vector<T> v{std::istream_iterator<T>(iss),
	std::istream_iterator<T>()};
	arg_vec.push_back(v);
}

std::vector<std::string> str_seq_to_int_vec(const std::string& arg_str) 
{
	std::vector<std::string> strings_vec;
	std::istringstream f(arg_str);
	std::string s;    
	while (getline(f, s, '\n')) {
		strings_vec.push_back(s);
	}
	return strings_vec;
}

template <typename T>
std::vector<std::vector<T>> MatrixRead() 
{
	std::ifstream file_to_read("file.txt");
	const std::string str_file((
				std::istreambuf_iterator<char>(file_to_read)),
				std::istreambuf_iterator<char>());
	std::vector<std::string> num_string_vec = str_seq_to_int_vec(str_file);
	std::vector<std::vector<T>> vec_2d_int;
	std::for_each (num_string_vec.begin(), num_string_vec.end(), 
		       [&vec_2d_int](std::string str_to_pass) {
		NumLinetoIntVec(vec_2d_int, str_to_pass);}
	);
	std::for_each(vec_2d_int.begin(), vec_2d_int.end(), 
		      [](std::vector<T> v) { 
		std::copy(v.begin(), v.end(), 
		std::ostream_iterator<T>(std::cout, " "));
		std::cout << std::endl;
	});
	return vec_2d_int;
}

#endif // READ_FROM_FILE
