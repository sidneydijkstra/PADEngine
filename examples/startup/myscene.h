
#ifndef MYSCENE_CLASS
#define MYSCENE_CLASS

#include "scene.h"
#include "entity.h"

using namespace pad;

class MyScene : public Scene {
	public:
		MyScene(std::string _name);
		~MyScene();
		
		void update() override;

		std::vector<Entity*> list;
	private:
};

#endif