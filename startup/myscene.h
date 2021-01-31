
#ifndef MYSCENE_CLASS
#define MYSCENE_CLASS

#include "scene.h"
#include "entity.h"

class MyScene : public Scene {
	public:
		MyScene();
		~MyScene();
		
		void update() override;
		void updateDescriptors(int _index, VkDescriptorSet _descriptorSets) override;

		Entity* _entity;
	private:
};

#endif