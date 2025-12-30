 #include <cstdint>
#include <iostream>
#include "bottlenecks.h"

void run_cpu_bottleneck() {
    std::cout << "[CPU bottleneck] starting\n";

    volatile uint64_t sum = 0;

    for (uint64_t i = 0; i < 500000000ULL; ++i) {
        sum += i;
    }

    std::cout << "[CPU bottleneck] done, sum = " << sum << "\n";
}
