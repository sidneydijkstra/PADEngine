#include "core.h"
#include "lightdemo/lightdemo.h"
#include "shaderdemo/shaderdemo.h"
#include "collisiondemo/collisiondemo.h"

using namespace pad;

int main() {

	Core core;

    LightDemo* sceneA = new LightDemo("light_demo");
    ShaderDemo* sceneB = new ShaderDemo("shader_demo");
    CollisionDemo* sceneC = new CollisionDemo("collision_demo");
    SceneManager::getInstance()->addScene(sceneA);
    SceneManager::getInstance()->addScene(sceneB);
    SceneManager::getInstance()->addScene(sceneC);
    SceneManager::getInstance()->setCurrentScene(sceneC);

    core.run();

    SceneManager::getInstance()->deleteScene("light_demo");
    SceneManager::getInstance()->deleteScene("shader_demo");
    SceneManager::getInstance()->deleteScene("collision_demo");

    delete sceneA;
    delete sceneB;
    delete sceneC;

    core.cleanup();

    return EXIT_SUCCESS;
}