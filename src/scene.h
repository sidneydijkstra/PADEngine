
#ifndef SCENE_CLASS
#define SCENE_CLASS

#include <stdlib.h>
#include <iostream>

#include "entity.h"
#include "camera.h"

class Scene : public Hierarchy {
	public:
		Scene(std::string _name);
		~Scene();

		virtual void update();
		void recreate(int _index);
		virtual void updateDescriptors(int _index, VkDescriptorSet _descriptorSets);

		std::string getName() { return _name; }
		Camera* getCamera();

		StorageBuffer<StorageBufferData>* _bufferData;
	private:
		Camera* _camera;
		std::string _name;
};
#endif