#ifndef SORT_BENCHMARK_PIGEONHOLE_H
#define SORT_BENCHMARK_PIGEONHOLE_H

#include <type_traits>
#include <vector>
#include <iostream>
#include <map>

template <class ForwardIt>
void pigeonhole(ForwardIt begin, ForwardIt end) {
    typedef typename std::remove_pointer<ForwardIt>::type ElementType;

    ElementType max = *begin;
    ElementType min = *begin;
    for (auto i = begin; i != end; i++) {
        if (*i > max) max = *i;
        if (*i < min) min = *i;
    }

    std::vector<ElementType> pigeonholes(max - min + 1, 0);
    std::vector<ElementType> usedIndexes;
    std::map<ElementType, ElementType> repeatedElementsCount;

    for (auto i = begin; i != end; i++) {
        ElementType index = *i - min;
        ElementType el = *i;
        pigeonholes[index] = el;

        if (repeatedElementsCount.count(*i) == 0) {
            repeatedElementsCount[*i] = 1;
        } else {
            repeatedElementsCount[*i] = repeatedElementsCount[*i] + 1;
        }

        usedIndexes.push_back(index);
    }

    auto currentPtr = begin;
    for (ElementType i = 0; i < pigeonholes.size(); i++) {
        auto it = std::find(usedIndexes.begin(), usedIndexes.end(), i);
        if (it != usedIndexes.end()) {
            for (ElementType j = 0; j < repeatedElementsCount[pigeonholes[i]]; j++) {
                *begin = pigeonholes[i];
                begin++;
            }
        }
    }
}

#endif //SORT_BENCHMARK_PIGEONHOLE_H