#include "myscene.h"

MyScene::MyScene() : Scene() {
	_entity = new Entity();

	_entity->getMesh()->loadObject("assets/viking_room.obj");
	_entity->getTexture()->loadTexture("assets/viking_room.png");
	this->addChild(_entity);
}


void MyScene::update() {
	this->getCamera()->move3D(5.0f);

	_entity->rotation.z += 0.2f * Time::getDeltaTime();
}

MyScene::~MyScene() {
	delete _entity;
}
