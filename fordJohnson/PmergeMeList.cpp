#include "PmergeMe.hpp"
#include "Jacobsthal.hpp"
#include "PmergePrints.hpp"
#include <cstddef>
#include <iostream>
#include <sys/time.h>

/*
// Ref: https://en.cppreference.com/cpp/iterator/advance
*/

//////////////// LIST FUNCTIONS //////////////////////////////////////////

template <typename T>
static typename std::list<T>::iterator get_it(std::list<T> &lst, size_t idx){
  typename std::list<T>::iterator it = lst.begin();
  std::advance(it, idx);
  return (it);
}

template <typename T>
static typename std::list<T>::const_iterator get_it(const std::list<T> &lst, size_t idx){
  typename std::list<T>::const_iterator it = lst.begin();
  std::advance(it, idx);
  return (it);
}


// returns index BEFORE which to insert
size_t  PmergeMe::binary_search(std::list<t_num_ptr> &main_chain,
                            const unsigned int num, size_t search_start,
                            size_t search_end, size_t &step_3_comparisons) {
  
  while (search_start < search_end) {
    size_t midpoint = search_start + (search_end - search_start) / 2;
    _lst_comparisons++;
    step_3_comparisons++;
    std::list<t_num_ptr>::const_iterator it = main_chain.begin();
    std::advance(it, midpoint);
    if (it->num < num) {
      search_start = midpoint + 1;
    } else {
      search_end = midpoint;
    }
  }
  return (search_start);
}

std::list<t_num_ptr>
PmergeMe::jacobsthal_insertion(const std::list<t_num_ptr> &pairs,
                               const std::list<t_num_ptr> &leftover){

  std::list<t_num_ptr> main_chain;
  std::list<t_num_ptr> b;
  std::list<t_jacob> sequence;
  size_t step_3_comparisons = 0;

  for (std::list<s_num_ptr>::const_iterator it = pairs.begin();
       it != pairs.end(); it++) {
    main_chain.push_back(it->ptr->a);
    b.push_back(it->ptr->b);
  }
  main_chain.insert(main_chain.begin(), pairs.begin()->ptr->b);
  if (!leftover.empty()) {
    b.push_back(leftover.front());
  }
  print_main_chain_and_b(main_chain, b);

  // JACOBSTHAL SEQUENCE
  print_description_for_step(4); // Step 3.1
  sequence = generate_sequence_list(b.size());
  print_jacobsthal_sequence(sequence);
  std::list<t_num_ptr>::iterator b_it;
  
  size_t end_idx;
  size_t idx_to_insert_before;
  for (std::list<t_jacob>::const_iterator it = sequence.begin();
       it != sequence.end(); it++) {
    end_idx = it->end_search_idx;
    b_it = get_it(b, (it->num - 1));
    idx_to_insert_before = binary_search(main_chain, b_it->num, 0,
                                         end_idx, step_3_comparisons);
    main_chain.insert(get_it(main_chain, idx_to_insert_before), *b_it);
  }
  print_main_chain_after_insert(main_chain);
  print_comparisons(step_3_comparisons);
  return (main_chain);
}

std::list<t_pair>
PmergeMe::make_pairwise_comparisons(const std::list<t_num_ptr> &numbers,
                                    size_t &step_1_comparisons) {

  std::list<t_pair> pairs;
  t_pair temp_pair;
  size_t size = numbers.size();

  if (numbers.size() % 2 != 0) {
    size = size - 1;
  }
  for (size_t i = 0; i < size; i = i + 2) {
    std::list<t_num_ptr>::const_iterator this_num;
    std::list<t_num_ptr>::const_iterator next_num;
    this_num = get_it(numbers, i);
    next_num = this_num;
    next_num++;
    if (this_num->num > next_num->num) {
      temp_pair.a = *this_num;;
      temp_pair.b = *next_num;
    } else {
      temp_pair.a = *next_num;
      temp_pair.b = *this_num;
    }
    _lst_comparisons++;
    step_1_comparisons++;
    pairs.push_back(temp_pair);
  }
  print_pairs(pairs);
  return (pairs);
}

std::list<t_num_ptr>
PmergeMe::merge_insertion_sort(const std::list<t_num_ptr> &numbers) {

  if (numbers.size() == 0 || numbers.size() == 1) {
    print_description_for_step(0);
    return (numbers);
  }

  std::list<t_pair> pairs;
  std::list<t_num_ptr> leftover;
  std::list<t_num_ptr> larger_numbers;
  size_t step_1_comparisons = 0;

  // STEP 1
  print_description_for_step(1);
  step_1_comparisons = 0;
  pairs = make_pairwise_comparisons(numbers, step_1_comparisons);
  if (numbers.size() % 2 != 0) {
    leftover.push_back(numbers.back());
  }
  print_leftover(leftover);
  print_comparisons(step_1_comparisons);

  // STEP 2
  print_description_for_step(2);
  t_num_ptr temp;
  for (std::list<t_pair>::iterator it = pairs.begin(); it != pairs.end(); it++) {
    temp.num = it->a.num;
    temp.ptr = &(*it);
    larger_numbers.push_back(temp);
  }
  larger_numbers = merge_insertion_sort(larger_numbers); // now sorted

  // STEP 3
  print_description_for_step(3);
  return (jacobsthal_insertion(larger_numbers, leftover));
}

void PmergeMe::sort_list(void) {

  if (LOGLVL >= 1) {
    std::cout << "START sort_list()\n" << std::endl;
  }
  // start time
  struct timeval start, end;
  gettimeofday(&start, 0);

  std::list<t_num_ptr> unsorted;
  t_num_ptr temp;
  for (size_t i = 0; i < _size; i++) {
    temp.num = _input[i];
    temp.ptr = NULL;
    unsorted.push_back(temp);
  }
  std::list<t_num_ptr> sorted = merge_insertion_sort(unsorted);
  for (std::list<t_num_ptr>::const_iterator it = sorted.begin();
    it != sorted.end(); it++){
    _lst_sorted.push_back(it->num);
  }

  // end time
  gettimeofday(&end, 0);
  _lst_time = end.tv_usec - start.tv_usec;

  if (LOGLVL >= 1) {
    std::cout << "\n"
              << "END sort_list()"
              << "\n"
              << "Total comparisons: " << _lst_comparisons << "\n"
              << std::endl;
  }
  return;
}
