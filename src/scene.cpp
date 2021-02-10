#include "scene.h"

Scene::Scene(std::string _name) : Hierarchy(){
	this->_camera = new Camera();
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

void Scene::updateDescriptors(int _index, Entity* _entity) {
	if(_entity->getType() != EntityType::CUSTOM){
		_light->getLightBuffer()->updateBuffer(_index, LightBufferObject{ _light->position, _camera->position, _light->color });
		_light->getLightBuffer()->updateDescriptor(_index, _entity->getDescriptorSet(_index), 3);
	}
}

Camera* Scene::getCamera() {
	return _camera;
}

Scene::~Scene() {
	delete _camera;
	delete _light;
}
