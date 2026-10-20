#include "PmergeMe.hpp"
#include "Jacobsthal.hpp"
#include "PmergePrints.hpp"
#include <cstddef>
#include <iostream>
#include <sys/time.h>

//////////////// VECTOR FUNCTIONS //////////////////////////////////////////

// returns index BEFORE which to insert
size_t  PmergeMe::binary_search(std::vector<t_num_ptr> &main_chain,
                            const unsigned int num, size_t search_start,
                            size_t search_end, size_t &step_3_comparisons) {

  while (search_start < search_end) {
    size_t midpoint = search_start + (search_end - search_start) / 2;
    _vec_comparisons++;
    step_3_comparisons++;
    if (main_chain[midpoint].num < num) {
      search_start = midpoint + 1;
    } else {
      search_end = midpoint;
    }
  }
  return (search_start);
}

std::vector<t_num_ptr>
PmergeMe::jacobsthal_insertion(const std::vector<t_num_ptr> &pairs,
                               const std::vector<t_num_ptr> &leftover){

  std::vector<t_num_ptr> main_chain;
  std::vector<t_num_ptr> b;
  std::vector<t_jacob> sequence;
  size_t step_3_comparisons = 0;

  for (std::vector<s_num_ptr>::const_iterator it = pairs.begin();
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
  sequence = generate_sequence_vec(b.size());
  print_jacobsthal_sequence(sequence);

  size_t end_idx;
  size_t idx_to_insert_before;
  for (std::vector<t_jacob>::const_iterator it = sequence.begin();
       it != sequence.end(); it++) {
    end_idx = it->end_search_idx;
    idx_to_insert_before = binary_search(main_chain, b[it->num - 1].num, 0,
                                         end_idx, step_3_comparisons);
    main_chain.insert(main_chain.begin() + idx_to_insert_before,
                      b[it->num - 1]);
  }
  print_main_chain_after_insert(main_chain);
  print_comparisons(step_3_comparisons);
  return (main_chain);
}

std::vector<t_pair>
PmergeMe::make_pairwise_comparisons(const std::vector<t_num_ptr> &numbers,
                                    size_t &step_1_comparisons) {

  std::vector<t_pair> pairs;
  t_pair temp_pair;
  size_t size = numbers.size();

  if (numbers.size() % 2 != 0) {
    size = size - 1;
  }
  for (size_t i = 0; i < size; i = i + 2) {
    if (numbers[i].num > numbers[i + 1].num) {
      temp_pair.a = numbers[i];
      temp_pair.b = numbers[i + 1];
    } else {
      temp_pair.a = numbers[i + 1];
      temp_pair.b = numbers[i];
    }
    _vec_comparisons++;
    step_1_comparisons++;
    pairs.push_back(temp_pair);
  }
  print_pairs(pairs);
  return (pairs);
}

std::vector<t_num_ptr>
PmergeMe::merge_insertion_sort(const std::vector<t_num_ptr> &numbers) {

  if (numbers.size() == 0 || numbers.size() == 1) {
    print_description_for_step(0);
    return (numbers);
  }

  std::vector<t_pair> pairs;
  std::vector<t_num_ptr> leftover;
  std::vector<t_num_ptr> larger_numbers;
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
  for (size_t i = 0; i < pairs.size(); i++) {
    temp.num = pairs[i].a.num;
    temp.ptr = &(pairs[i]);
    larger_numbers.push_back(temp);
  }
  larger_numbers = merge_insertion_sort(larger_numbers); // now sorted

  // STEP 3
  print_description_for_step(3);
  return (jacobsthal_insertion(larger_numbers, leftover));
}

void PmergeMe::sort_vector(void) {

  if (LOGLVL >= 1) {
    std::cout << "START sort_vector()\n" << std::endl;
  }
  // start time
  struct timeval start, end;
  gettimeofday(&start, 0);

  std::vector<t_num_ptr> unsorted;
  t_num_ptr temp;
  for (size_t i = 0; i < _size; i++) {
    temp.num = _input[i];
    temp.ptr = NULL;
    unsorted.push_back(temp);
  }
  std::vector<t_num_ptr> sorted = merge_insertion_sort(unsorted);
  for (size_t i = 0; i < sorted.size(); i++) {
    _vec_sorted.push_back(sorted[i].num);
  }

  // end time
  gettimeofday(&end, 0);
  _vec_time = end.tv_usec - start.tv_usec;

  if (LOGLVL >= 1) {
    std::cout << "\n"
              << "END sort_vector()"
              << "\n"
              << "Total comparisons: " << _vec_comparisons << "\n"
              << std::endl;
  }
  return;
}