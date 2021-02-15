#include "scenemanager.h"

namespace pad {

SceneManager::SceneManager() {
	_currentScene = nullptr;
}

SceneManager* SceneManager::getInstance() {
	static SceneManager _instance;
	return &_instance;
}

void SceneManager::deleteScene(std::string name) {
	_scenes.erase(name);
}

void SceneManager::addScene(Scene* scene) {
	_scenes.insert(std::pair<std::string, Scene*>(scene->getName(), scene));
}

Scene* SceneManager::getScene(std::string name) {
	return _scenes.find(name)->second;
}

void SceneManager::setCurrentScene(Scene* scene) {
	_currentScene = scene;
}

void SceneManager::deleteInstance() {
	//delete _instance;
	//_instance = nullptr;
}

void SceneManager::setCurrentScene(const char* name) {
	_currentScene = this->getScene(name);
}

SceneManager::~SceneManager() {
	_scenes.clear();
}

}