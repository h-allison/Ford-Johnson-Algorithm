#include "PmergePrints.hpp"


void	print_description_for_step(int step){
	if (LOGLVL == 0) {
		return;
	}
	if (LOGLVL >= 2) {
		switch (step)
		{
			case 0:
				std::cout << "\t"
				<< "Merge insertion base case reached: there is only 1 larger number."
				<< std::endl;
				break;
			case 1:
				std::cout << "\n"
				<< "Step 1: Make pairwise comparisons of (n / 2) disjoint pairs of elements."
				<< "\n" << "\t" << "(If n is odd, leave one element out.)\n" << std::endl; 
				break;
			case 2:
				std::cout << "\n"
				<< "Step 2: Sort the (n/2) larger numbers, found in step 1, "
				<< "by merge insertion (recurse to step 1).\n" << std::endl;
				break;
			case 3:
				// Step 3.0
				std::cout << "\n"
				<< "Step 3: Split the elements into groups \"a\" (higher elements of each pair)\n"
				<< "\t" << "and \"b\" (lowers element of each pair). If there was a leftover, put it at the end of b."
				<< std::endl;
				break;
			case 4:
				// Step 3.1
				std::cout << "\n"
				<< "Step 3 (cont'd): " << "Insert the remaining b's into main_chain, using binary insertion," << "\n"
				<< "\t" << "in the order of (to paraphrase)..." << "b[jacob[i]], b[jacob[i] - 1], b[jacob[i] - 2],\n"
				<< "\t" << "... down to b[jacob[i - 1] + 1], then i++" << "\n"
				<< std::endl;
				break;
			default:
				break;
		}
	}
}

void	print_comparisons(size_t comparisons){
	if (LOGLVL >= 1){
		std::cout << "\t" << "This step: " << comparisons << " comparisons."
		<< std::endl;
	}
}
