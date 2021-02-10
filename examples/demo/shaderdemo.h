
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
		RenderPass* _renderPass;
		Entity* _plane;
};

class Canvas : public Entity {
	public:
		Canvas() : Entity() {
			this->_type = EntityType::CUSTOM;
			this->getMesh()->loadShape(MeshType::PLANE);
			this->getMaterial()->setMaterial("mat_custom");
			this->setupDescriptorSets();
		};
		~Canvas() {
		
		};

		void update() override {
			
		};

		void updateDescriptors(int _index) override {
			this->getUniformBuffer()->updateDescriptor(_index, _descriptorSets[_index], 0);
		};

	private:
};

#endif