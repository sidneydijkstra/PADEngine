#include "myscene.h"

int amount = 0;
MyScene::MyScene(std::string _name) : Scene(_name) {
	list = std::vector<Entity*>();
	
	for (size_t i = 0; i < 10; i++) {
		Entity* e = new Entity();
		e->position = Vector3((rand() % 10) - 5, (rand() % 10) - 5, (rand() % 10) - 5);
		// e->rotation = Vector3((rand() % 360), (rand() % 360), (rand() % 360));
		list.push_back(e);
		this->addChild(e);
	}

}

void MyScene::update() {
	this->getCamera()->move3D(5.0f);
}

MyScene::~MyScene() {
	for (auto e : list)
		delete e;
	list.clear();
}
