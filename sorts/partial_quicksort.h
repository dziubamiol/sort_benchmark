//
// Created by Misha Dziuba on 29.04.2020.
//

#ifndef SORT_BENCHMARK_PARTIAL_QUICKSORT_H
#define SORT_BENCHMARK_PARTIAL_QUICKSORT_H

#include <type_traits>
#include <iostream>

template <class ForwardIt, class T>
ForwardIt partition (T pivot, ForwardIt begin, ForwardIt end) {
    begin = begin - 1;
    end = end + 1;

    while (true) {
        do {
            begin++;
        } while (*begin < pivot);
        do {
            end--;
        } while (*end > pivot);
        if (begin >= end) return end;

        typedef typename std::remove_pointer<ForwardIt>::type ElementType;

        ElementType temp = *begin;
        *begin = *end;
        *end = temp;
    }
}

template <class ForwardIt>
ForwardIt partition2 (ForwardIt begin, ForwardIt end) {
    typedef typename std::remove_pointer<ForwardIt>::type ElementType;
    ElementType pivot = *end;

    ForwardIt i = begin - 1;

    for (auto j = begin; j != end; j++)
    {
        if (*j <= pivot)
        {
            i++;
            ElementType temp = *i;
            *i = *j;
            *j = temp;
        }
    }
    i++;
    ElementType temp = *i;
    *i = *end;
    *end = temp;

    return i;
}

template <class ForwardIt, class T>
void partial_quicksort (ForwardIt begin, ForwardIt end, T maxToSort) {
    if (begin < end) {

        //ForwardIt pivot = partition2<ForwardIt> (begin, end);
        ForwardIt pivot = partition(*(begin + (end - begin) / 2), begin, end);

        //std::cout << "Recursion depth " << recursionDepth << " last index " << end - begin << " distance to pivot " << pivot - begin << " maxToSort " << maxToSort <<'\n';

        partial_quicksort<ForwardIt, T> (begin, pivot, maxToSort);

        T distance = (pivot - begin);
        if (distance < maxToSort - 1) {
            partial_quicksort<ForwardIt, T> (pivot + 1, end, maxToSort);
        }
    }
}

// end - is exact finish of array
template <class ForwardIt>
void quick_sort (ForwardIt begin, ForwardIt end) {
    if (begin < end) {
        ForwardIt position = partition(*(begin + (end - begin) / 2), begin, end);

        quick_sort(begin, position);
        quick_sort(position + 1, end);
    }
}

template <class ForwardIt>
void partial_benchmark (ForwardIt begin, ForwardIt end) {
    typedef typename std::remove_pointer<ForwardIt>::type ElementType;

    ElementType maxToSort = *(begin + 1 + (end - begin) / 2); // + 1 is offset to make it more fun
    //quick_sort(begin, end - 1);
    partial_quicksort<ForwardIt, ElementType> (begin, end - 1, maxToSort);
}

#endif //SORT_BENCHMARK_PARTIAL_QUICKSORT_H
