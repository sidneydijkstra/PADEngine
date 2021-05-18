#include "core.h"
#include "lightdemo/lightdemo.h"
#include "shaderdemo/shaderdemo.h"
#include "objectdemo/objectdemo.h"

using namespace pad;

int main() {

	Core core;

    LightDemo* sceneA = new LightDemo("light_demo");
    ShaderDemo* sceneB = new ShaderDemo("shader_demo");
    ObjectDemo* sceneC = new ObjectDemo("object_demo");

    SceneManager::getInstance()->addScene(sceneA);
    SceneManager::getInstance()->addScene(sceneB);
    SceneManager::getInstance()->addScene(sceneC);

    SceneManager::getInstance()->setCurrentScene(sceneA);

    core.run();

    SceneManager::getInstance()->deleteScene("light_demo");
    SceneManager::getInstance()->deleteScene("shader_demo");
    SceneManager::getInstance()->deleteScene("object_demo");

    delete sceneA;
    delete sceneB;
    //delete sceneC;

    core.cleanup();

    return EXIT_SUCCESS;
}