#include "collisiondemo.h"

CollisionDemo::CollisionDemo(std::string _name) : Scene(_name, PerspectiveType::ORTHOGRAPHIC) {
	Entity* planea = new Entity2D();
	planea->position.x = 300;
	planea->position.y = 300;
	this->addChild(planea);
	list.push_back(planea);

	Entity* planeb = new Entity2D();
	planeb->position.x = 100;
	planeb->position.y = 100;
	planea->addChild(planeb);
	list.push_back(planeb);
}

void CollisionDemo::update() {
	if (Input::getKeyDown(KeyCode::Q))
		SceneManager::getInstance()->setCurrentScene("shader_demo");
	if (Input::getKeyDown(KeyCode::E))
		SceneManager::getInstance()->setCurrentScene("light_demo");
}

CollisionDemo::~CollisionDemo() {
	for (auto e : list)
		delete e;
	list.clear();
}
