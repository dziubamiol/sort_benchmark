#include <iostream>
#include <random>
#include <fstream>
#include <algorithm>
#include <string>
#include <array>

#ifndef SORT_BENCHMARK_GENERATOR_H
#define SORT_BENCHMARK_GENERATOR_H

/* Цю частину лаби я почав писати в першу чергу,
 * тому, по правді кажучи, приклад даної фнкції був наданий мені паном Геращенко С.
 * Цим самим він врятував мене від смертельної панічної атаки яка могла бути викликаною
 * принципово іншим механізмом алокації пам'яті та роботи замикань аніж в JavaScript.
 * Біль пройшла, концепції стали зрозумілими, йдемо далі.
 * Дякую за увагу.
 *
 * Generate array with uniform distribution with lower and upper boundaries
 * */

template <class ForwardIt, class T>
void generateUniformArray(ForwardIt first, ForwardIt last, T lowerBound, T upperBound) {
    std::default_random_engine generator{std::random_device{}() };
    std::uniform_int_distribution<T> distribution(lowerBound, upperBound);

    std::generate(first, last, [&]() {
        return distribution(generator);
    });
}

/*
 * Generate array with normal distribution with lower and upper boundaries
 */

template<class ForwardIt, class T>
void generateNormalArray(ForwardIt first, ForwardIt last, T lowerBound, T upperBound) {
    std::default_random_engine generator{std::random_device{}()};
    // double використано для бусту швидкості, для великих mean stddev ф-я якось дивно працює (на i7 16gb ram висла намертво)
    std::normal_distribution<double> distribution(5.0, 3.0);

    // map distribution value to our boundaries
    auto getNormalWithBoundaries = [=](double distribution) {
        const auto boundarySize = (double)(upperBound - lowerBound);

        return (boundarySize / 10) * distribution + lowerBound / 10;
    };

    std::generate(first, last, [&]() {
        auto n = (int)(getNormalWithBoundaries(distribution(generator)));
        return n;
    });
}



/*
 * Write array to file
 */

template <class ForwardIt>
void writeArrayToFile(ForwardIt first, ForwardIt last, const std::string& name) {
    std::ofstream file;
    file.open(name);

    for (ForwardIt i = first; i != last; i++) {
        file << *i << ' ';
    }
    file.close();
}

/*
 * Get set filename
 */

template <class A, class S>
std::string getFileName(A arrSize, S spread, unsigned int index, unsigned int funcNameIndex) {
    std::array<std::string, 4> funcNames = {"uniform", "uniform", "uniform", "normal"};

    return "sets/" + std::to_string(arrSize) + '-' + std::to_string(spread) + '-' + std::to_string(index) + '-' + funcNames[funcNameIndex] + ".txt";
}

//#include "generator.cpp"

void createUniformArrayFile();

#endif //SORT_BENCHMARK_GENERATOR_H
