
#ifndef MYSCENE_CLASS
#define MYSCENE_CLASS

#include "scene.h"
#include "entity.h"

using namespace pad;

class LightDemo : public Scene {
	public:
		LightDemo(std::string _name);
		~LightDemo();
		
		void update() override;

		std::vector<Entity*> list;
	private:
};

#endif