
#define NDEBUG

#include <iostream>

#include "core.h"

int main() {
    Core core;

    try {
        core.run();
    }
    catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}