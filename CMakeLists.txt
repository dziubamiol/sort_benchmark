cmake_minimum_required(VERSION 3.16)
project(sort_benchmark)

set(CMAKE_CXX_STANDARD 20)

add_executable(sort_benchmark main.cpp generator/generator.h generator/generator.cpp benchmark/benchmark.h benchmark/benchmark.cpp sorts/pigeonhole.cpp sorts/pigeonhole.h sorts/partial_quicksort.cpp sorts/partial_quicksort.h sorts/introsort.cpp sorts/introsort.h sorts/heapsort.cpp sorts/heapsort.h sorts/insertionsort.cpp sorts/insertionsort.h misc/status_bar.cpp misc/status_bar.h)