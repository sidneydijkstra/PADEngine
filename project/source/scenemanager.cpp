#include "scenemanager.h"

SceneManager::SceneManager() {

}

SceneManager* SceneManager::getInstance() {
	if (!_instance) {
		_instance = new SceneManager();
	}
	return _instance;
}

Scene* SceneManager::createScene(string name) {
	Scene* _scene = new Scene();
	_scene->name() = name;

	if (auto lowerbound = _scenes.lower_bound(_scene->name());
		lowerbound != _scenes.end() && !_scenes.key_comp()(_scene->name(), lowerbound->first)) {
		throw std::runtime_error("woooowwww hold your horses! This name already exists, delete your existing scene or choose a different name.");
	}
	else {
		_scenes.insert(lowerbound, std::make_pair(_scene->name(), _scene));
	}
	
}

void SceneManager::addScene(Scene* scene) {
	this->_scenes.insert(std::pair<string, Scene*>(scene->name(), scene));
}

Scene* SceneManager::getScene(string name) {
	return this->_scenes.find(name)->second;
}

void SceneManager::deleteInstance() {
	delete _instance;
	_instance = nullptr;
}

SceneManager::~SceneManager() {
	std::map<std::string, Scene*>::iterator scene_it;
	for (scene_it = _scenes.begin(); scene_it != _scenes.end(); ++scene_it) {
		if (scene_it->second != NULL) {
			delete scene_it->second;
		}
	}
	_scenes.clear();
}