#include "scene.h"

Scene::Scene() {
	_children = std::vector<Entity*>();
	_camera = new Camera();

	_children.push_back(new Entity());
	_children.push_back(new Entity());
	_children[1]->setPosition(Vector3(0, -1, 0));

	_children[0]->texture()->loadTexture("assets/logo.png");
	_children[1]->texture()->loadTexture("assets/banaan.jpg");
}

void Scene::update() {
	_camera->move3D(5.0f);
}

void Scene::recreate(int _index) {
	for (Entity* e : _children) {
		e->recreate(_index);
	}
}

Camera* Scene::camera() {
	return _camera;
}

Scene::~Scene() {
	for (Entity* e : _children) {
		delete e;
	}
	_children.clear();
}
