#include <iostream>
#include <array>
#include <algorithm>
#include "generator/generator.h"
#include "benchmark/benchmark.h"

int main(int argc, char** argv) {
    std::cout << argc << argv[0] << std::endl;

    for(unsigned int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "generate_set")) {
            createUniformArrayFile();
        } else if (!strcmp(argv[i], "run_benchmark")) {
            runBenchmark();
        } else {
            std::cout << "Invalid command specified" << std::endl;
        }
    }

    return 0;
}