#include "myscene.h"

MyScene::MyScene() : Scene() {
	for (size_t i = 0; i < 10; i++) {
		Entity* entity = new Entity();
		entity->getPostion().y = i + 0.2f;
		this->getChildren().push_back(entity);
	}
}


void MyScene::update() {
	this->getCamera()->move3D(5.0f);

	int count = 0;
	for(Entity* ent : this->getChildren()){
		float x = ent->getPostion().x;
		float newX = (x + 5 * Time::getDeltaTime());

		count++;
		if (newX > 5 + count) {
			newX = 0;
		}
		ent->getPostion().x = newX;
	}
}

MyScene::~MyScene() {
}
