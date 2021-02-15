#include "core.h"
#include "myscene.h"

using namespace pad;

int main() {

	Core core;

    LightDemo* scene = new LightDemo("myscene");
    SceneManager::getInstance()->addScene(scene);
    SceneManager::getInstance()->setCurrentScene(scene);

    core.run();

    SceneManager::getInstance()->deleteScene("myscene");

    delete scene;

    core.cleanup();

    return EXIT_SUCCESS;
}