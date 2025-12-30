#include <iostream>
#include <vector>
#include <cstdlib>
#include "bottlenecks.h"

void run_memory_bottleneck() {
    std::cout << "[Memory bottleneck] starting\n";

    const size_t SIZE = 200 * 1024 * 1024; // ~200MB
    std::vector<int> data(SIZE);

    volatile int sum = 0;

    for (size_t i = 0; i < SIZE; i += 64) {
        sum += data[i];
    }

    std::cout << "[Memory bottleneck] done, sum = " << sum << "\n";
}
