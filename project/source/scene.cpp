#include "scene.h"

Scene::Scene() {
	_children = std::vector<Entity*>();

	_children.push_back(new Entity());
	_children.push_back(new Entity());
	_children[1]->pos.x = -1;

	_children[0]->texture()->loadTexture("assets/logo.png");
	_children[1]->texture()->loadTexture("assets/banaan.jpg");
}

void Scene::update() {
}

void Scene::recreate(int _index) {
	for (Entity* e : _children) {
		e->recreate(_index);
	}
}

Scene::~Scene() {
	for (Entity* e : _children) {
		delete e;
	}
	_children.clear();
}
