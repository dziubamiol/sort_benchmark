#ifndef SORT_BENCHMARK_INSERTIONSORT_H
#define SORT_BENCHMARK_INSERTIONSORT_H

#include <type_traits>

template <class ForwardIt>
void insertionsort (ForwardIt begin, ForwardIt end) {
    ForwardIt i, j;
    for (i = begin + 1; i != end; i++) {
        typedef typename std::remove_pointer<ForwardIt>::type ElementType;

        ElementType key = *i;
        j = i - 1;

        while (j >= begin && *j > key) {
            *(j + 1) = *j;
            j--;
        }
        *(j + 1) = key;
    }
}

#endif //SORT_BENCHMARK_INSERTIONSORT_H
