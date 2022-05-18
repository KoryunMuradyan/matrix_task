#ifndef __TEST_GAUS_METHOD_HPP__
#define __TEST_GAUS_METHOD_HPP__

#include <algorithm>
#include <sstream>
#include <fstream>
#include <iterator>     // back_inserter
#include <vector>

void NumLinetoIntVec(std::vector<std::vector<float>>& arg_vec, 
		std::string& arg_str)
{
    std::istringstream iss(arg_str);
    std::vector<float> v{std::istream_iterator<float>(iss),
                       std::istream_iterator<float>()};
    arg_vec.push_back(v);
}

std::vector<std::string> str_seq_to_int_vec(std::string& arg_str)
{
	std::vector<std::string> strings_vec;
	std::istringstream f(arg_str);
	std::string s;    
	while (getline(f, s, '\n')) {
		//std::cout  <<  s  <<  std::endl;
		strings_vec.push_back(s);
	}
	return strings_vec;
}

void test_gaus_method()
{
	std::ifstream file_to_read("file.txt");
	std::string str_file((std::istreambuf_iterator<char>(file_to_read)),
					std::istreambuf_iterator<char>());
	std::vector<std::string> num_string_vec = str_seq_to_int_vec(str_file);
	str_file.clear();
	std::vector<std::vector<float>> vec_2d;
	std::for_each (num_string_vec.begin(), num_string_vec.end(), 
			[&vec_2d](std::string str_to_pass) 
			{NumLinetoIntVec(vec_2d, str_to_pass);}
	);
	std::for_each(vec_2d.begin(), vec_2d.end(), 
		[](std::vector<float> v) { 
			std::copy(v.begin(), v.end(), 
			std::ostream_iterator<float>(std::cout, " "));
			std::cout << std::endl;
		}
	);
}

#endif // end of __TEST_GAUS_METHOD_HPP__
