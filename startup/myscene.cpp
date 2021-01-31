#include "myscene.h"

int amount = 0;
MyScene::MyScene() : Scene() {
	_entity = new Entity();
	this->addChild(_entity);
}


void MyScene::update() {
	this->getCamera()->move3D(5.0f);
}

void MyScene::updateDescriptors(int _index, VkDescriptorSet _descriptorSets) {
	Scene::updateDescriptors(_index, _descriptorSets);
}

MyScene::~MyScene() {
	delete _entity;
}
