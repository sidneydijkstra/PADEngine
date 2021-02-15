
#ifndef SHADERDEMO_CLASS
#define SHADERDEMO_CLASS

#include "scene.h"
#include "canvas.h"
#include "scenemanager.h"

using namespace pad;

class ShaderDemo : public Scene {
	public:
		ShaderDemo(std::string _name);
		~ShaderDemo();
		
		void update() override;
	private:
		RenderPass* _renderPass;
		Entity* _plane;
};

#endif