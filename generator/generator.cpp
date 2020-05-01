#include <algorithm>
#include <string>
#include <array>
#include "generator.h"
#include "../misc/status_bar.h"

/*
 * Generate uniform spread array and write it to file with name
 */

void createUniformArrayFile() {
    std::array<unsigned int, 4> distributionSizes = {UINT32_MAX, 10000, UINT16_MAX, UINT32_MAX};
    std::array<unsigned int, 5> arraySizes = {10,10000, 100000, 300000, 1000000};

    typedef void (*funcPtr)(unsigned int* f, unsigned int* l, unsigned int lB, unsigned int uB);
    std::array<funcPtr, 4> callbacks = {generateUniformArray, generateUniformArray, generateUniformArray, generateNormalArray};

    std::array<unsigned int, 1000000> arr{};

    uint8_t ready = 0;
    for (uint8_t i = 0; i < 5; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            for (uint8_t z = 0; z < 5; z++) {
                callbacks[j](arr.begin(), arr.begin() + arraySizes[i], 0, distributionSizes[j]);
                writeArrayToFile(arr.begin(), arr.begin() + arraySizes[i], getFileName(arraySizes[z], distributionSizes[j], i, j));
                ready++;

                double readyPercents = ready / (5.0 * 4.0 * 5.0);
                show_status_bar(readyPercents, 50, '#', '\n');
            }
        }
    }
}
