# The Ford-Johnson-Algorithm
### A guide to understanding Knuth's description of merge-insertion

The Ford-Johnson algorithm, also known as merge-insertion sort, is a sorting algorithm described by Donald Knuth in Volume 3 of [The Art of Computer Programming](https://en.wikipedia.org/wiki/The_Art_of_Computer_Programming).

The algorithm is designed to minimize the number of *comparisons* required to sort a given group of elements, in the worst case.

If you've never heard of merge-insertion sort, that's probably because it's not of any real use. Among students in the C/C++ curriculum at 42, the algorithm is infamous, as the subject of our final and most complex C++ exercise module.

From its name alone, you might imagine a simple combo of merge-sort and insertion-sort. Merge- and insertion-sort are indeed both involved, but the algorithm also requires pairing elements, as well as inserting elements into a chain. The insertion is done based on a formula that uses a sequence of numbers, called the Jacobsthal sequence. All steps of the alogrithm are part of a single recursion. Many summaries of Knuth's description skip or gloss over this recursion, and many students make the mistake of believing that only the last step is recursive -- I made this mistake too, at first.

To prove that you've implemented the alogorithm correctly, you should count the number of comparisons performed by your program to sort *n* numbers. This number will match a table of maximum comparisons shown on page 186 of *The Art of Computer Programming, Vol. 3*.

