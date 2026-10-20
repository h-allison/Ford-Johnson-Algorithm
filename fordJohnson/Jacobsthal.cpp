
#include "Jacobsthal.hpp"
#include <cstddef> // for size_t
#include <vector>
#include <list>

unsigned int	jacobsthal(const int n){

	// each num = previous num + 2 × (num before previous num).
	// jacobsthal sequence = 1, 1, 3, 5, 11, 21, 43, 85...
	
	if (n <= 0){
		return (0);
	}
	else if (n == 1){
		return (1);
	}
	else return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

std::vector<t_jacob>	generate_sequence_vec(const size_t &len_of_b){

	std::vector<t_jacob> sequence;
	size_t	jacobs_num;
	size_t previous_jacobs_num = 1; // jacobsthal[0] = 1
	int	i = 1; // index 0 was already added to main_chain
	size_t	added = 1;
	t_jacob	data;
	
	while (previous_jacobs_num <= len_of_b){
		jacobs_num = jacobsthal(i);
		while (jacobs_num > previous_jacobs_num){
			if (jacobs_num <= len_of_b){
				data.num = jacobs_num;
				data.end_search_idx = jacobs_num + added - 1;
				sequence.push_back(data);
				added++;
			}
			jacobs_num--;
		}
		previous_jacobs_num = jacobsthal(i);
		i++;
	}
	return (sequence);
}

std::list<t_jacob>	generate_sequence_list(const size_t &len_of_b){

	std::list<t_jacob> sequence;
	size_t	jacobs_num;
	size_t previous_jacobs_num = 1; // jacobsthal[0] = 1
	int	i = 1; // index 0 was already added to main_chain
	size_t	added = 1;
	t_jacob	data;
	
	while (previous_jacobs_num <= len_of_b){
		jacobs_num = jacobsthal(i);
		while (jacobs_num > previous_jacobs_num){
			if (jacobs_num <= len_of_b){
				data.num = jacobs_num;
				data.end_search_idx = jacobs_num + added - 1;
				sequence.push_back(data);
				added++;
			}
			jacobs_num--;
		}
		previous_jacobs_num = jacobsthal(i);
		i++;
	}
	return (sequence);
}