# PmergeMe
PmergeMe is an implementation of the Ford Johnson algorithm, created as part of CPP_09, the last C++ module in the C/C++ core curriculum at 42 Berlin.

The program uses both std::vector and std::list containers, simply to compare their efficiency.

### Build:

`make` Print level = input, output, time to process

`make debug` Print level += intermediate sorting steps

`make verbose` Print level += explanatory excerpts


### Run:

`./PmergeMe 3 8 1 11 5 2 7 6 10 9 4`

`./PmergeMe $(shuf -i 1-20 -n 20 | tr "\n" " ")`

`./PmergeMe` will suggest the argument above