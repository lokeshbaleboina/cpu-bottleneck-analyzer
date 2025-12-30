#include <iostream>
#include <thread>
#include <vector>
#include <cstdint>
#include "bottlenecks.h"

void worker(int id) {
    volatile uint64_t sum = 0;

    for (uint64_t i = 0; i < 300000000ULL; ++i) {
        sum += i;
    }

    std::cout << "Thread " << id << " finished\n";
}

void run_thread_bottleneck() {
    std::cout << "[Thread bottleneck] starting\n";

    const int NUM_THREADS = 4;
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "[Thread bottleneck] done\n";
}
