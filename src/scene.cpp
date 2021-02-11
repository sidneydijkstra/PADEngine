#include "scene.h"

Scene::Scene(std::string _name, Type type) : Hierarchy(){
	this->_camera = new Camera(Type::PERSPECTIVE);
	this->_name = _name;

	_light = new Light();
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

void Scene::updateDescriptors(int _index, VkDescriptorSet _descriptorSets) {
	_light->getLightBuffer()->updateBuffer(_index, LightBufferObject{ _light->position, _camera->position, _light->color });
	_light->getLightBuffer()->updateDescriptor(_index, _descriptorSets, 3);
}

Camera* Scene::getCamera() {
	return _camera;
}

Scene::~Scene() {
	delete _camera;
	delete _light;
}
