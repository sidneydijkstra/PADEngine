#include "myscene.h"

MyScene::MyScene() : Scene() {
	_entity = new Entity();

	_entity->getMesh()->loadObject("assets/viking_room.obj");
	_entity->getTexture()->loadTexture("assets/viking_room.png");
	this->addChild(_entity);
}


void MyScene::update() {
	this->getCamera()->move3D(5.0f);
}

MyScene::~MyScene() {
	delete _entity;
}
