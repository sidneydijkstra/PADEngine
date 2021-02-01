#include "scene.h"

Scene::Scene(std::string _name) : Hierarchy(){
	this->_camera = new Camera();
	this->_name = _name;

	_bufferData = new StorageBuffer<StorageBufferData>();
	for (size_t i = 0; i < SwapChainHandler::getInstance()->getSwapChainImagesSize(); i++) {
		_bufferData->updateBuffer(i, StorageBufferData{ glm::vec3(3, 6, 2) });
	}
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
	this->_bufferData->updateDescriptor(_index, _descriptorSets, 3);
}

Camera* Scene::getCamera() {
	return _camera;
}

Scene::~Scene() {
	delete _bufferData;
}
