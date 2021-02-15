
#ifndef COLLISIONDEMO_CLASS
#define COLLISIONDEMO_CLASS

#include "scene.h"
#include "entity.h"
#include "scenemanager.h"

class CollisionDemo : public Scene {
	public:
		CollisionDemo(std::string _name);
		~CollisionDemo();
		
		void update() override;

		std::vector<Entity*> list;
	private:
};

class Entity2D : public Entity {
	public:
		Entity2D() {
			this->scale.x = 100;
			this->scale.y = 100;
			this->scale.z = 100;
			this->getMaterial()->setMaterial("mat_normal2D_PBR");
			this->setupDescriptorSets();
		};

		~Entity2D() {
		
		};
};

#endif