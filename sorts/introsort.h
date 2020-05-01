//
// Created by Misha Dziuba on 30.04.2020.
//

#ifndef SORT_BENCHMARK_INTROSORT_H
#define SORT_BENCHMARK_INTROSORT_H

#include "insertionsort.h"
#include "heapsort.h"
#include <cmath>

template <class ForwardIt, class T>
void introsort (ForwardIt begin, ForwardIt end, T depthLimit) {
    T size = end - begin;

    if (size < 5) { // heuristic value
        insertionsort<ForwardIt> (begin, end + 1);
        return;
    }
    if (depthLimit == 0) {
        heapsort<ForwardIt> (begin, end + 1);
        return;
    } else {
        if (begin < end) {
            ForwardIt position = partition(*(begin + (end - begin) / 2), begin, end);

            introsort(begin, position, depthLimit - 1);
            introsort(position + 1, end, depthLimit - 1);
        }
    }
}

template <class ForwardIt>
void introsort_benchmark (ForwardIt begin, ForwardIt end) {
    typedef typename std::remove_pointer<ForwardIt>::type ElementType;

    ElementType depthLimit = std::floor(std::log(end - begin));

    introsort(begin, end - 1, depthLimit);
}



#endif //SORT_BENCHMARK_INTROSORT_H
