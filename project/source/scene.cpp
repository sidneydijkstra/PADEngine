#include "scene.h"

Scene::Scene() {
	_children = std::vector<Entity*>();
	_camera = new Camera();
}

void Scene::update() {
}

void Scene::recreate(int _index) {
	for (Entity* e : _children) {
		e->recreate(_index);
	}
}

std::vector<Entity*>& Scene::getChildren() {
	return _children;
}

Camera* Scene::getCamera() {
	return _camera;
}

Scene::~Scene() {
	for (Entity* e : _children) {
		delete e;
	}
	_children.clear();
}
