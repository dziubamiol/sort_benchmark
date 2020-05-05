#include <string>
#include <iostream>
#include <cmath>

void show_status_bar(double percentage, const uint8_t size, char symbol, char delimiter) {
    auto filledSize = (int) std::floor(percentage * size);
    //uint8_t unfilledSize = size - filledSize;
    auto intPercents = (int) std::floor(percentage * 100);

    std::cout << "[";
    for (uint8_t i = 0; i < size; i++) {
        if (i < filledSize) std::cout << symbol;
        else std::cout << ' ';
    }
    std::cout << "] " << intPercents << '%' << delimiter << std::flush;
}
