
#ifndef SHADERDEMO_CLASS
#define SHADERDEMO_CLASS

#include "scene.h"
#include "entity.h"
#include "scenemanager.h"

class ShaderDemo : public Scene {
	public:
		ShaderDemo(std::string _name);
		~ShaderDemo();
		
		void update() override;
	private:
};

#endif