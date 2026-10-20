#ifndef JACOBSTHAL_HPP
# define JACOBSTHAL_HPP

#include <cstddef>
#include <list>
#include <vector>

typedef struct s_jacob {
    size_t  num;
    size_t  end_search_idx;
  } t_jacob;

unsigned int	jacobsthal(const int n);
std::vector<t_jacob>	generate_sequence_vec(const size_t &size_of_b);
std::list<t_jacob>	generate_sequence_list(const size_t &size_of_b);
#endif