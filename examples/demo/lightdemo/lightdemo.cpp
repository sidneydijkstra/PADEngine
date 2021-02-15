#include "lightdemo.h"

LightDemo::LightDemo(std::string _name) : Scene(_name, PerspectiveType::PERSPECTIVE) {
	list = std::vector<Entity*>();
	this->addChild(_light);
	
	for (size_t i = 0; i < 10; i++) {
		Entity* e = new Entity();
		e->position = Vector3((rand() % 10) - 5, (rand() % 10) - 5, (rand() % 10) - 5);
		list.push_back(e);
		this->addChild(e);
	}
}

void LightDemo::update() {
	this->getCamera()->move3D(5.0f);

	this->_light->position.x += amountX * Time::getDeltaTime();
	this->_light->position.y += amountY * Time::getDeltaTime();
	this->_light->position.z += amountZ * Time::getDeltaTime();

	amountX = this->_light->position.x > 5 || this->_light->position.x < -5 ? -amountX : amountX;
	amountY = this->_light->position.y > 5 || this->_light->position.y < -5 ? -amountY : amountY;
	amountZ = this->_light->position.z > 5 || this->_light->position.z < -5 ? -amountZ : amountZ;

	if (Input::getKeyDown(KeyCode::Q))
		SceneManager::getInstance()->setCurrentScene("collision_demo");
	if (Input::getKeyDown(KeyCode::E))
		SceneManager::getInstance()->setCurrentScene("shader_demo");
}

LightDemo::~LightDemo() {
	for (auto e : list)
		delete e;
	list.clear();
}
