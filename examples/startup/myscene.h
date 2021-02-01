
#ifndef MYSCENE_CLASS
#define MYSCENE_CLASS

#include "scene.h"
#include "entity.h"

class MyScene : public Scene {
	public:
		MyScene();
		~MyScene();
		
		void update() override;

		std::vector<Entity*> list;
	private:
};

#endif