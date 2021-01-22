#include "scene.h"

Scene::Scene() {
	_children = std::vector<Entity*>();
	_camera = new Camera();

	for (size_t i = 0; i < 250; i++) {
		_children.push_back(new Entity());

		int x = (rand() % 50) - 25;
		int y = (rand() % 50) - 25;
		int z = (rand() % 50) - 25;

		_children[i]->setPosition(Vector3(x, y, z));
	}

	for (size_t i = 250; i < 500; i++) {
		_children.push_back(new Entity());

		int x = (rand() % 50) - 25;
		int y = (rand() % 50) - 25;
		int z = (rand() % 50) - 25;

		_children[i]->setPosition(Vector3(x, y, z));
		_children[i]->texture()->loadTexture("assets/banaan.jpg");
		_children[i]->mesh()->loadShape(MeshType::PLANE);
	}

	for (size_t i = 500; i < 600; i++) {
		_children.push_back(new Entity());

		int x = (rand() % 50) - 25;
		int y = (rand() % 50) - 25;
		int z = (rand() % 50) - 25;

		_children[i]->setPosition(Vector3(x, y, z));
		_children[i]->texture()->loadTexture("assets/viking_room.png");
		_children[i]->mesh()->loadObject("assets/viking_room.obj");
		// _children[i]->setMaterial(MaterialManager::getInstance()->get("mat_red_PBR"));
	}
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
