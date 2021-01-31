#include "scene.h"

Scene::Scene() : Hierarchy(){
	_camera = new Camera();

	_bufferData = new StorageBuffer();
	for (size_t i = 0; i < SwapChainHandler::getInstance()->getSwapChainImagesSize(); i++) {
		_bufferData->updateBuffer(i, StorageBufferData{ glm::vec3(2, 3, 0) });
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
