#include "objectdemo.h"

ObjectDemo::ObjectDemo(std::string _name) : Scene(_name) {
	Entity* obj = new Entity();
	obj->getMesh()->loadObject("assets/viking_room.obj");
	obj->getTexture()->loadTexture("assets/viking_room.png");
	this->addChild(obj);
	list.push_back(obj);
}

void ObjectDemo::update() {
	this->getCamera()->move3D(5.0f);

	if (Input::getKeyDown(KeyCode::Q))
		SceneManager::getInstance()->setCurrentScene("shader_demo");
	if (Input::getKeyDown(KeyCode::E))
		SceneManager::getInstance()->setCurrentScene("light_demo");
}

ObjectDemo::~ObjectDemo() {
	for (auto e : list)
		delete e;
	list.clear();
}
