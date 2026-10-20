#include "PmergeMe.hpp"
#include "Jacobsthal.hpp"
#include "PmergePrints.hpp"
#include <iostream>

PmergeMe::PmergeMe(void)
    : _size(0), _input(NULL), _vec_comparisons(0), _vec_time(0),
      _lst_comparisons(0), _lst_time(0) {}

PmergeMe::PmergeMe(const unsigned int *input, const size_t size)
    : _size(size), _input(new unsigned int[size]), _vec_comparisons(0), _vec_time(0),
                          _lst_comparisons(0), _lst_time(0) {
  for (size_t i = 0; i < size; i++) {
    _input[i] = input[i];
  }
}

PmergeMe::~PmergeMe(void) {
  if (_input != NULL) {
    delete[] _input;
  }
};

PmergeMe::PmergeMe(const PmergeMe &src)
    : _size(src._size), _input(new unsigned int[_size]),
		_vec_sorted(src._vec_sorted), _vec_comparisons(src._vec_comparisons), _vec_time(src._vec_time),
      	_lst_sorted(src._lst_sorted), _lst_comparisons(src._lst_comparisons), _lst_time(src._lst_time){
  	for (size_t i = 0; i < _size; i++) {
    	_input[i] = src._input[i];
  	}
};

PmergeMe &PmergeMe::operator=(const PmergeMe &src) {
  if (this != &src) {
    _size = src._size;
	_vec_sorted = src._vec_sorted;
    _vec_comparisons = src._vec_comparisons;
	_vec_time = src._vec_time;
	_lst_sorted = src._lst_sorted;
    _lst_comparisons = src._lst_comparisons;
	_lst_time = src._lst_time;
 	if (_input != NULL) {
		delete[] _input;
  	}
	_input = new unsigned int[_size];
  	for (size_t i = 0; i < _size; i++) {
    	_input[i] = src._input[i];
  	}
  }
  return (*this);
};

void PmergeMe::validate_and_print_sorted(void) const {
  
  std::list<unsigned int>::const_iterator lst_it = _lst_sorted.begin();

	if (_vec_sorted.size() != _size){
		std::cout << "ERROR: _vec_sorted.size() != _size" << std::endl;
	}
	if (_lst_sorted.size() != _size){
		std::cout << "ERROR: _lst_sorted.size() != _size" << std::endl;
	}
  std::cout << "After:	";
	if (_vec_sorted.empty() || _lst_sorted.empty()){
		std::cout << "empty";
		return;
	}
	for (size_t i = 0; i < _size; i++){
		if (i != 0 && _vec_sorted[i - 1] > _vec_sorted[i]){
			std::cout << "ERROR: Results are not fully sorted." << "\n"
				<< "elements [" << i - 1 << "] > elements [" << i << "]" << "\n"
				<< _vec_sorted[i - 1] << " > " << _vec_sorted[i] << ""
				<< std::endl;
				return;
		}
		if (_vec_sorted[i] != *lst_it){
			std::cout << "ERROR: _vec_sorted() != _lst_sorted()" << std::endl;
			return;
		}
		std::cout << _vec_sorted[i] << " ";
		lst_it++;
	}
	std::cout << std::endl;
}

void PmergeMe::print_input(void) const {

  std::cout << "Before:	";
  if (_size == 0) {
    std::cout << "empty";
  } else {
    for (size_t i = 0; i < _size; i++) {
      std::cout << _input[i] << " ";
    }
  }
  std::cout << std::endl;
}

void PmergeMe::sort(void) {

  print_input();
  sort_vector();
  sort_list();
  validate_and_print_sorted();
  std::cout << "Time to process " << _size
            << " elements with std::vector: " << _vec_time << " us"
            << std::endl;
  std::cout << "Time to process " << _size
            << " elements with std::list: " << _lst_time << " us"
            << std::endl;
}