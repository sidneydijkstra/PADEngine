
#ifndef LIGHTDEMO_CLASS
#define LIGHTDEMO_CLASS

#include "scene.h"
#include "entity.h"
#include "scenemanager.h"

class LightDemo : public Scene {
	public:
		LightDemo(std::string _name);
		~LightDemo();
		
		void update() override;

		std::vector<Entity*> list;
	private:
		int amountX = 2;
		int amountY = 2;
		int amountZ = 2;
};

#endif