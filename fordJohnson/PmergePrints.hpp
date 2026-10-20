#ifndef PMERGEPRINTS_H
# define PMERGEPRINTS_H

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "PmergeMe.hpp"

#ifndef LOGLVL
# define LOGLVL 0
#endif


void	print_description_for_step(int step);
void	print_comparisons(size_t comparisons);

template <typename T>	
void print_leftover(const T &leftover){

	if (LOGLVL == 0){
		return;
	}
	if (LOGLVL >= 1){
		std::cout << "\t" << "Leftover: [ ";
		if (!leftover.empty()){
			std::cout << leftover.front().num << " ]";
		}
		else {
			std::cout << "none ]" << std::endl;
		}
		std::cout << std::endl;
	}
}

template <typename T>
void	print_jacobsthal_sequence(const T &sequence){
	if (LOGLVL == 0){
		return;
	}
	if (LOGLVL >= 1){
		std::cout << "\t" << "Jacobsthall Sequence:" << "\n\t";
		for (typename T::const_iterator it = sequence.begin(); it != sequence.end(); it++){
			std::cout << it->num << " "; }
		std::cout << "\n\t" << "Ending Search Index (in Knuth's terms, where index 0 = '1'):"
			<< "\n\t";
		for (typename T::const_iterator it = sequence.begin(); it != sequence.end(); it++){
			std::cout << it->end_search_idx << " ";
		}
	}
	std::cout << std::endl;
}

template <typename T>
static void print_pairs(const T &pairs){
	
	if (LOGLVL == 0){
		return;
	}
	if (LOGLVL >= 1){
		if (pairs.empty()){
			return;
		}
		std::cout << "\n" << "\t" << "Pairs, sorted internally:" << "\n"
			<< "\t" << "{ ";
		typename T::const_iterator it = pairs.begin();
		while (it != pairs.end()){
			std::cout << "[" << it->a.num << ", " << it->b.num << "] ";
			it++;
		}
		std::cout << "}" << std::endl;
	}
}

template <typename T>
static void print_main_chain_and_b(const T &main_chain, const T &b){
	
	if (LOGLVL == 0){
		return;
	}
	if (LOGLVL >= 1){
		std::cout << "\n" << "\t"
			<<	"main_chain (above) -- b (below)" 
			<< "\n\t";
		for (typename T::const_iterator it = main_chain.begin();
			it != main_chain.end(); it++){
			std::cout << it->num << " ";
	}
	std::cout << "\n\t  ";
	for (typename T::const_iterator it = b.begin();
		it != b.end(); it++){
			std::cout << it->num << " ";
	}
	std::cout << std::endl;
	}
}

template <typename T>
static void print_main_chain_after_insert(const T &main_chain){
	
	if (LOGLVL == 0){
		return;
	}
	if (LOGLVL >= 1){
		std::cout << "\n" << "\t"
			<<	"After insertions, main_chain:" 
			<< "\n\t";
		for (typename T::const_iterator it = main_chain.begin();
			it != main_chain.end(); it++){
			std::cout << it->num << " ";
		}
		std::cout << "\n";
	}
}

#endif