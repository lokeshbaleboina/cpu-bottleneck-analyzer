#include <iostream>
#include <cstdint>

int main() {
    std::cout << "CPU Bottleneck Analyzer: Stage 2 (CPU burn)\n";

    volatile uint64_t sum = 0;

    for (uint64_t i = 0; i < 500000000ULL; ++i) {
        sum += i;
    }

    std::cout << "Sum = " << sum << "\n";
    return 0;
}
