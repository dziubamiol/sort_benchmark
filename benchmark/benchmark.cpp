#include <array>
#include <algorithm>
#include <fstream>
#include "benchmark.h"
#include "./../generator/generator.h"
#include "./../sorts/pigeonhole.h"
#include "./../sorts/partial_quicksort.h"
#include "./../sorts/introsort.h"
#include "../misc/status_bar.h"

void runBenchmark() {
    std::array<SortCallback<unsigned int*>, 5> sorts = {std::stable_sort, std::sort, introsort_benchmark<unsigned int*>, partial_benchmark<unsigned int*>, pigeonhole<unsigned int*>};
    std::array<std::string, 5> sortNames = {"stable_sort", "sort", "introsort", "partial_quicksort", "pigeonhole"};

    std::array<unsigned int, 5> arraySizes = {10, 10000, 100000, 300000, 1000000};
    std::array<unsigned int, 4> distributionSizes = {UINT32_MAX, 10000, UINT16_MAX, UINT32_MAX};
    std::array<std::string, 4> funcNames = {"uniform", "uniform", "uniform", "normal"};

    int ready = 0;
    for (uint8_t i = 0; i < 5; i++) { // array sizes
        for (uint8_t j = 0; j < 4; j++) { // function names and sizes
            for (uint8_t z = 0; z < 5; z++) { // repeats per function
                std::string filename = getFileName(arraySizes[i], distributionSizes[j], z, j);

                std::array<unsigned int, 1000000> test = {};
                std::ifstream dataset(filename);
                std::cout << "Starting " << filename << '\n';

                if(dataset.is_open()) {
                    unsigned int parsed;
                    for (unsigned int k = 0; k < 10000; k++) {
                        dataset >> parsed;
                        //std::cout << typeid(parsed).name() << parsed << ' ';
                        test[k] = parsed;
                    }

                    for (int sortIndex = 0; sortIndex < 4; sortIndex++) {
                        benchmark<unsigned int *, unsigned int>(sorts[sortIndex], test.begin(),test.begin() + arraySizes[i], 5, sortNames[sortIndex], false);

                        ready++;
                        double readyPercents = ready / (5.0 * 4.0 * 5.0 * 4.0);
                        show_status_bar(readyPercents, 50, '#', '\n');
                    }
                }
                dataset.close();
            }
        }
    }
}