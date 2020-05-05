#ifndef SORT_BENCHMARK_BENCHMARK_H
#define SORT_BENCHMARK_BENCHMARK_H

#include <iostream>
#include <chrono>
#include <vector>

template<class ForwardIt>
using SortCallback = void (*)(ForwardIt begin, ForwardIt end);

struct BenchmarkResult {
    std::vector<double> timeDeltas;
    double mean;
};

template<class ForwardIt, class T>
BenchmarkResult benchmark(SortCallback<ForwardIt> sort, ForwardIt begin, ForwardIt end, uint8_t repeats, const std::string &name, const std::string& fileName, bool display = false) {
    std::vector<double> timeDeltas = {};
    std::array<unsigned int, 1000000> copyArray = {}; // bad part, seems like std array doesnt support any dynamic allocation, even with templates

    std::ofstream file;
    file.open("results/" + name + ".txt", std::ios_base::app);

    std::cout << "Starting " << name << '\n';
    file << "---- " << fileName << " ----\n";

    for (uint8_t i = 0; i < repeats; i++) {
        // make copy of old array to new
        std::copy(begin, end, copyArray.begin());

        auto cpBegin = copyArray.begin();
        auto cpEnd = cpBegin + (end - begin);

        if (display) {
            std::cout << "Before sort: ";
            for (auto j = cpBegin; j != cpEnd; j++) {
                std::cout << *j << ',';
            }
            std::cout << '\n';
        }

        // begin test
        auto timeStart = std::chrono::steady_clock::now();

        sort(cpBegin, cpEnd);

        auto timeFinish = std::chrono::steady_clock::now();
        std::chrono::duration<double> sortTimeDelta = timeFinish - timeStart;

        std::cout << "Sorted in: " << sortTimeDelta.count() << "s\n";
        file << "Sorted in: " << sortTimeDelta.count() << "s\n";
        timeDeltas.push_back(sortTimeDelta.count());

        if (display) {
            for (auto j = cpBegin; j != cpEnd; j++) {
                std::cout << *j << ',';
            }
            std::cout << '\n';
        }
    }

    double totalDelta = 0.0;
    for (auto delta : timeDeltas) {
        totalDelta += delta;
    }
    double mean = totalDelta / timeDeltas.size();

    std::cout << "Mean time for " << name << ": " << mean << "s\n";
    file << "Mean time for " << name << ": " << mean << "s\n";
    file.close();

    BenchmarkResult results = {
            timeDeltas,
            mean
    };

    return results;
}

void runBenchmark();


#endif //SORT_BENCHMARK_BENCHMARK_H
