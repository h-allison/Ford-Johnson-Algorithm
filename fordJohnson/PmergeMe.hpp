#ifndef PMERGEME_H
#define PMERGEME_H

#include <cstddef>
#include <list>
#include <vector>

typedef struct s_pair t_pair;

typedef struct s_num_ptr {
  unsigned int num;
  const t_pair *ptr;
} t_num_ptr;

typedef struct s_pair {
  t_num_ptr a;
  t_num_ptr b;
} t_pair;

class PmergeMe {

public:
  PmergeMe(void);
  PmergeMe(const unsigned int *input, const size_t size);
  PmergeMe(const PmergeMe &src);
  PmergeMe &operator=(const PmergeMe &src);
  ~PmergeMe(void);

  void sort(void);

private:
  size_t _size;
  unsigned int *_input;
  
  std::vector<unsigned int> _vec_sorted;
  unsigned int _vec_comparisons;
  long _vec_time;

  std::list<unsigned int> _lst_sorted;
  unsigned int _lst_comparisons;
  long _lst_time;

  //////////////////////

  void print_input(void) const;
  void validate_and_print_sorted(void) const;

  //// std::vector

  void sort_vector(void);
  
  std::vector<t_num_ptr>
  merge_insertion_sort(const std::vector<t_num_ptr> &batch);
  
  std::vector<t_pair>
  make_pairwise_comparisons(const std::vector<t_num_ptr> &numbers,
                            size_t &step_1_comparisons);
  
  std::vector<t_num_ptr>
  jacobsthal_insertion(const std::vector<t_num_ptr> &pairs,
                       const std::vector<t_num_ptr> &leftover);

  size_t
  binary_search(std::vector<t_num_ptr> &main_chain, const unsigned int num,
    size_t search_start, size_t search_end, size_t &step_3_comparisons);
  
  //// std::list
  
  void sort_list(void);
  
  std::list<t_num_ptr>
  merge_insertion_sort(const std::list<t_num_ptr> &batch);
  
  std::list<t_pair>
  make_pairwise_comparisons(const std::list<t_num_ptr> &numbers,
                            size_t &step_1_comparisons);
  
  std::list<t_num_ptr>
  jacobsthal_insertion(const std::list<t_num_ptr> &pairs,
                       const std::list<t_num_ptr> &leftover);

  size_t
  binary_search(std::list<t_num_ptr> &main_chain, const unsigned int num,
    size_t search_start, size_t search_end, size_t &step_3_comparisons);

};
#endif
