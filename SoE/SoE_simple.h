#include <vector> 

#define RandomAccessIterator typename
#define Integer typename

template <RandomAccessIterator I, Integer N>
void mark_sieve(I first, I last, N factor) {
    // assert(first != last)
    *first = false;
    while (last-first > factor) {
        first = first + factor;
        *first = false;
    }
}

template <RandomAccessIterator I, Integer N>
void sift(I first, N n) {
    I last = first + n;
    std::fill(first, first + n, true);
    N i(0);
    N index_square(3);
    N factor(3);
    while (index_square < n) {
        // invariant: index_square = 2i^2 + 6i + 3
        if (first[i]) {  // if the candidate is prime
            mark_sieve(first + index_square,
                       last, // last
                       factor); // factor
        }
        ++i;
        index_square += factor;
        factor += N(2);
        index_square += factor;
    }
}
