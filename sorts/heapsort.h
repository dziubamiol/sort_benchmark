#ifndef SORT_BENCHMARK_HEAPSORT_H
#define SORT_BENCHMARK_HEAPSORT_H

#include <type_traits>

template <class ForwardIt, class T>
void heapify (ForwardIt begin, T size, T rootIndex) {
    T left = rootIndex * 2 + 1;
    T right = rootIndex * 2 + 2;
    T highest = rootIndex;

    if (left < size && *(begin + left) > *(begin + highest))
        highest = left;
    if (right < size && *(begin + right) > *(begin + highest))
        highest = right;

    if (highest != rootIndex) {
        T temp = *(begin + highest);
        *(begin + highest) = *(begin + rootIndex);
        *(begin + rootIndex) = temp;

        heapify(begin, size, highest);
    }
}

template <class ForwardIt>
void heapsort (ForwardIt begin, ForwardIt end) {
    typedef typename std::remove_pointer<ForwardIt>::type ElementType;

    ElementType size = end - begin;

    for (ElementType i = 0; i <= size / 2 - 1; i++) {
        heapify<ForwardIt, ElementType> (begin, size, size / 2 - 1 - i);
    }

    for (ElementType i = 1; i <= size; i++) {
        ElementType index = (size - i);
        ElementType temp = *begin;
        *begin = *(begin + index);
        *(begin + (size - i)) = temp;

        heapify<ForwardIt, ElementType> (begin, index, 0);
    }
}

#endif //SORT_BENCHMARK_HEAPSORT_H
