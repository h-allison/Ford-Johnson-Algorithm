#include "PmergeMe.hpp"
#include <cstdlib> // for stroul
#include <limits>
#include <exception>
#include <iostream>
#include <vector>

bool	is_duplicate(unsigned int n, unsigned int *input, int size){

	for (int i = 0; i < size; i++){
		if (input[i] == n){
			return (true);
		}
	}
	return (false);
}

unsigned int	argv_to_uint(const std::string &arg, unsigned int *input, int previous_size){

	if (arg.empty()){
		throw std::invalid_argument("arg list contains at least one empty string. Try this instead...\n./PmergeMe $(shuf -i 1-20 -n 20 | tr \"\\n\" \" \")");
	}
	if (arg.size() > 10){
		throw std::invalid_argument("bad input, string is too long to be an int");
	}
	for (std::string::const_iterator it = arg.begin();
		it != arg.end(); it++){
			if (*it < '0' || *it > '9'){
				throw std::invalid_argument("invalid input. expected positive ints, each as a separate arg");
			}
	}
	size_t	num = strtoul(arg.c_str(), NULL, 10);
	if (num <= 0 || num > static_cast<size_t>(std::numeric_limits<int>::max())){
		throw std::invalid_argument("input contains number that is not a positive integer");
	}
	if (is_duplicate(num, input, previous_size)){
		throw std::invalid_argument("input contains duplicate number");
	}
	return (static_cast<unsigned int>(num));
}

int	main(int argc, char *argv[]){
	
	if (argc < 2){
		std::cout << "Expected: <argument list of positive ints>\n"
		<< "Try this:\n" << "./PmergeMe $(shuf -i 1-20 -n 20 | tr \"\\n\" \" \")"
		<< std::endl;
		return (1);
	}
	
	unsigned int	input[argc - 1];
	int i = 0;
	while (i + 1 < argc){
		try {
			input[i] = argv_to_uint(argv[i + 1], input, i);
		}
		catch (std::exception &e){
			std::cerr << e.what() << std::endl;
			return (1);
		}
		i++;
	}

	PmergeMe	sorter(input, argc - 1);
	sorter.sort();
}
