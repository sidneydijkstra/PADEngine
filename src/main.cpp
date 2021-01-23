
#define NDEBUG

#include <iostream>

#include "core.h"

int main() {
    // std::ios::sync_with_stdio(false); // -> speed of fps in console
    Core core;

    Scene* scene = new Scene();

    core.run(scene);

    delete scene;

    core.cleanup();

    return EXIT_SUCCESS;
}