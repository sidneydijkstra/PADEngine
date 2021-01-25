#include "core.h"
#include "myscene.h"

int main() {

	Core core;

    MyScene* scene = new MyScene();

    core.run(scene);

    delete scene;

    core.cleanup();

    return EXIT_SUCCESS;
}