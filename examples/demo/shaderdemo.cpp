#include "shaderdemo.h"

ShaderDemo::ShaderDemo(std::string _name) : Scene(_name) {
}

void ShaderDemo::update() {
	this->getCamera()->move3D(5.0f);

	if (Input::getKeyDown(KeyCode::Q))
		SceneManager::getInstance()->setCurrentScene("light_demo");
	if (Input::getKeyDown(KeyCode::E))
		SceneManager::getInstance()->setCurrentScene("light_demo");
}

ShaderDemo::~ShaderDemo() {
}
