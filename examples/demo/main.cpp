#include "core.h"
#include "lightdemo.h"
#include "shaderdemo.h"

int main() {

	Core core;

    LightDemo* sceneA = new LightDemo("light_demo");
    ShaderDemo* sceneB = new ShaderDemo("shader_demo");
    SceneManager::getInstance()->addScene(sceneA);
    SceneManager::getInstance()->addScene(sceneB);
    SceneManager::getInstance()->setCurrentScene(sceneA);

    core.run();

    SceneManager::getInstance()->deleteScene("light_demo");
    SceneManager::getInstance()->deleteScene("shader_demo");

    delete sceneA;
    delete sceneB;

    core.cleanup();

    return EXIT_SUCCESS;
}