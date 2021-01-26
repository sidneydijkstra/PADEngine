#include "scene.h"

Scene::Scene() : Hierarchy(){
	_camera = new Camera();
}

void Scene::update() {
}

void Scene::recreate(int _index) {
	std::vector<Hierarchy*> list = this->getChildren();
	for (size_t i = 0; i < list.size(); i++) {
		Entity* ent = (Entity*)list[i];
		ent->recreate(_index);
	}
}

Camera* Scene::getCamera() {
	return _camera;
}

Scene::~Scene() {
}
