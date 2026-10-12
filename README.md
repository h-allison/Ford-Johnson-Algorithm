# The Ford-Johnson-Algorithm

The Ford-Johnson algorithm, aka merge insertion sort, is a sorting algorithm described by Donald Knuth in Volume 3 of [The Art of Computer Programming](https://en.wikipedia.org/wiki/The_Art_of_Computer_Programming).

![The algorirthm, as described by Knuth](images/knuth_text_algorithm_steps.png)

The algorithm is designed to minimize the number of *comparisons* required to sort a given group of elements, in the worst case. Among students in the C/C++ curriculum at 42, the Ford-Johnson / merge-insertion algorithm is infamous, as the subject of our final and most complex C++ exercise module.

[Here an illustration?]

# The steps of *merge insertion* for $n$ elements

## Step 1 (merge)
> i) Make pairwise comparisons of $\lfloor n/2 \rfloor$ disjoint pairs of elements. (If $n$ is odd, leave one element out.)

This step is easy. Out of $n$ elements, create $n/2$ pairs. If one element is leftover, save it to the side.

![Step 1, Part 1](/images/step_1_part_1.gif)

Sort each pair internally. This will require 1 comparison per pair. *Is pair[0] > pair[1]?* Keep track of the total number of comparisons you perform, from beginning to end of the algorithm.

![Step 1, Part 2](/images/step_1_part_2.gif)

## Step 2 (recurse)
> ii) Sort the $\lfloor n/2 \rfloor$ larger numbers, found in step (i), by merge insertion.

Step 2 of merge insertion is... merge insertion. Perform the same algorithm in its entirety (Steps 1-3) on the larger elements found in Step 1.

![Step 2 cycling through Step 1](images/step_2_fast.gif)


The program will "wind up" by cycling through Steps 1-2 repeatedly (as seen in the dizzying animation above), and when the base case is reached (there is only one element), it will "unwind" back through as many rounds of Step 3.

When the recursion eventually unwinds, the pairs that we've been creating and sorting will be unwrapped again. For this reason, it's essential to keep track of each element's pair, throughout the recursion. In the illustration, I'm using paperclips to keep track of pairs. In the code, it's pointers.

```
typedef struct s_num_ptr {
  unsigned int num;
  const t_pair *ptr;
} t_num_ptr;
```

---

### Winding Up, in Slow Motion:
Here is a slower breakdown of what's happening in the animated example. We ended Step 1 with a group of pairs, and each pair's elements ordered.

Step 2 is to the take larger element of each pair as our new input, and begin the alorithm again at Step 1. I'm paperclipping each larger number on top of its pair.

![Taking the Larger Numbers Only](images/step_2_take_larger.gif)

Back to Step 1. Out of $n$ elements, create $n/2$ pairs. If one element is leftover, save it to the side.

![Make pairs again](images/step_2_make_pairs.jpg)

Again, sort each pair internally. *Is pair[0] > pair[1]?* We add these comparisons to our running total of comparisons performed.

In the illustrated example, it just so happened that {8, 11} and {5, 7} were already ordered, so no swapping was required.

Now we arrive at Step 2 again. Again we take the larger numbers, make pairs, order pairs, and repeat...





## 3) Split elements into 2 chains. Perform insertion according to sequence formula.

> iii) Name the elements $a_1, a_2, \ldots, a_{\lfloor n/2 \rfloor}, b_1, b_2, \ldots, b_{\lceil n/2 \rceil}$ as in (7), where $a_1 \le a_2 \le \cdots \le a_{\lfloor n/2 \rfloor}$ and $b_i \le a_i$ for $1 \le i \le \lfloor n/2 \rfloor$; call $b_1$ and the $a$'s the "main chain." Insert the remaining $b$'s into the main chain, using binary insertion, in the following order, leaving out all $b_j$ for $j > \lceil n/2 \rceil$:
>
>$`\quad b_3, b_2;\; b_5, b_4;\; b_{11}, b_{10}, \ldots, b_6;\; \ldots;\; b_{t_k}, b_{t_k - 1}, \ldots, b_{t_{k-1}+1};\; \ldots \qquad`$

This step is very dense, so let's comb through it line by line.

My explanations will draw from additional text on the same page, as well as the diagram on page 184.

<BR>

> Name the elements $a_1, a_2, \ldots, a_{\lfloor n/2 \rfloor}, b_1, b_2, \ldots, b_{\lceil n/2 \rceil}$ as in (7), where $a_1 \le a_2 \le \cdots \le a_{\lfloor n/2 \rfloor}$ and $b_i \le a_i$ for $1 \le i \le \lfloor n/2 \rfloor$;

- Break the elements into 2 groups, keeping them in order.
- Group "a" ($a_1, a_2$, ...), includes up to n/2 elements. (If n is odd, round down)
- Group "b" ($b_1, b_2$, ...) includes up to n/2 elements. (If n is odd, round up)

	This lower bracket notation ... ${\lfloor n/2 \rfloor}$ ... means floor, aka "n/2 rounded down."
	
	This upper bracket notation ... ${\lceil n/2 \rceil}$ ... means ceiling, aka "n/2" rounded up."

- As the elements were already ordered, the first element of "b" should be less than the first element of "a."

<BR>

> Call $b_1$ and the $a$'s the "main chain." 

- Remove the first element of "b" and add it as the new first element of "a." This group ( $b_1$ and all the $a$`s) will from now on be referred to as the "main chain."

> Insert the remaining $b$'s into the main chain, using binary insertion, in the following order, leaving out all $b_j$ for $j > \lceil n/2 \rceil$:
>
>$`\quad b_3, b_2;\; b_5, b_4;\; b_{11}, b_{10}, \ldots, b_6;\; \ldots;\; b_{t_k}, b_{t_k - 1}, \ldots, b_{t_{k-1}+1};\; \ldots \qquad`$

Now we will insert $b$'s into the main chain according to a particular formula that uses a special sequence of numbers. The these tiny subscripted values are getting hard to read... and there's further explanation about them in the text, so let's zoom out here.

![Jacobsthal_explanation](/images/knuth_text_jacobsthal_explanation.png)

- Determine the next element of $b$ to be inserted into the main chain.
- The next element is determined according to this sequence, which will not mean anything to you at first glance:

![a close-up of this last line](images/knuth_text_jacobsthal.png)

What is $t$ here, and what is $k$? In the next paragraph, Knuth defines $t$ as the Jacobsthal Numbers (1, 3, 5, 11...), and $k$ is the index of $t$. (Note that in this math world, the very first index is 1, not 0).

The first number of the Jacobsthal Numbers is $1$.
Therefore: $t_1 = 1$, $b_{t_1} = b_1$, and $b_1 = $ the first element of b. We've already inserted $b_1$ when we created the main chain. After $1$, the next number in the Jacobsthal sequence is $3$. So in this case...
- $t_2 = 1$
- $t_{k-1}$ = $t_


## What's Involved in Merge-Insertion (a preview)

From the name alone, you might imagine a simple combo of merge-sort and insertion-sort. Merge- and insertion-sort are indeed both involved, but the algorithm also requires pairing elements, as well as inserting elements into a chain in a particular order. The insertion is done based on a formula that uses a sequence of numbers, called the Jacobsthal sequence. More on this later.

The trickiest part is... that all steps of the alogrithm are part of a single recursion. Many summaries of merge-insertion tend to skip or gloss over this recursion, and many students make the mistake of believing that only part of the alogrithm is recursive. I made this mistake too, at first.

To test whether you've implemented the right algorithm, you should count the number of comparisons that your program performs to sort *n* numbers. If done correctly, this number will match the table of maximum comparisons shown on page 186 of *The Art of Computer Programming, Vol. 3*.

## Brushing up on Merge Sort & Insertion Sort

Before digging into the Ford-Johnson, it's nice to brush up on merge sort and insertion sort. For one thing, you'll you have to implement  both as part of FJ. For another thing, it's going to be super helpful for your understanding of FJ to remember the particular advantages of merge sort vs. insertion sort, and in what cases each of the two is efficient.

- Merge Sort // TODO link to merge sort summary
- Insertion Sort // TODO link to insertion sort summary

## Jacobsthal Numbers

There's also one more thing you might like to know about before reading the Knuth text, and that's the Jacobsthal Numbers. The Jacobsthal numbers are an sequence of integers related to Fibonacci numbers, which will be used in our formula for insertion.

The sequence begins with 0 and 1. Each following number in the sequence is equal to... the previous number + two times the number before the previous number.


> 0, 1, 2, 3, 5, 11, 21, 43, 85, 171, ...

The definition of the sequence may sound convoluted, but you'll find that you can write a function to generate these numbers very easily.

You might find it helpful to do this right now, because in the text, Knuth is going to make reference to the Jabobsthal Numbers out of nowhere (without naming them, just describing how they're generated), and as soon as they've been introduced, you're going to have to create an additional sequence with them. Better to have some familiarity first.

As for why these numbers are relevant to the algorithm... By the time you're finished, this will hopefully make a lot more sense, but will likely still remain a least somewhat magical. For now, you may just enjoy noticing that each number in the sequence is about double the previous number, give or take 1.

# Reading Knuth

> In general, merge insertion proceeds as follows for $n$ elements:
>
> i) Make pairwise comparisons of $\lfloor n/2 \rfloor$ disjoint pairs of elements. (If $n$ is odd, leave one element out.)
>
> ii) Sort the $\lfloor n/2 \rfloor$ larger numbers, found in step (i), by merge insertion.
>
> iii) Name the elements $a_1, a_2, \ldots, a_{\lfloor n/2 \rfloor}, b_1, b_2, \ldots, b_{\lceil n/2 \rceil}$ as in (7), where $a_1 \le a_2 \le \cdots \le a_{\lfloor n/2 \rfloor}$ and $b_i \le a_i$ for $1 \le i \le \lfloor n/2 \rfloor$; call $b_1$ and the $a$'s the "main chain." Insert the remaining $b$'s into the main chain, using binary insertion, in the following order, leaving out all $b_j$ for $j > \lceil n/2 \rceil$:
>
>$$b_3, b_2;\; b_5, b_4;\; b_{11}, b_{10}, \ldots, b_6;\; \ldots;\; b_{t_k}, b_{t_k - 1}, \ldots, b_{t_{k-1}+1};\; \ldots \qquad