#include "myscene.h"

MyScene::MyScene() : Scene() {
	Entity* entity = new Entity();

	entity->mesh()->loadObject("assets/viking_room.obj");
	entity->texture()->loadTexture("assets/viking_room.png");
	this->getChildren().push_back(entity);
}


void MyScene::update() {
	this->getCamera()->move3D(5.0f);
}

MyScene::~MyScene() {
}
