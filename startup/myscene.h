
#ifndef MYSCENE_CLASS
#define MYSCENE_CLASS

#include "scene.h"

class MyScene : public Scene {
	public:
		MyScene();
		~MyScene();
		
		void update() override;

	private:
};

#endif