#include <iostream>
#include <string>
#include "bottlenecks.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage:\n";
        std::cout << "  ./analyzer cpu\n";
        std::cout << "  ./analyzer memory\n";
        std::cout << "  ./analyzer thread\n";
        return 0;
    }

    std::string mode = argv[1];

    if (mode == "cpu") {
        run_cpu_bottleneck();
    } else if (mode == "memory") {
        run_memory_bottleneck();
    } else if (mode == "thread") {
        run_thread_bottleneck();
    } else {
        std::cout << "Unknown mode\n";
    }

    return 0;
}

