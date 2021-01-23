
#ifndef SCENE_CLASS
#define SCENE_CLASS

#include <stdlib.h>

#include "entity.h"
#include "camera.h"

class Scene {
	public:
		Scene();
		~Scene();

		virtual void update();
		void recreate(int _index);

		std::vector<Entity*>& getChildren();
		Camera* getCamera();

	private:
		std::vector<Entity*> _children;
		Camera* _camera;
};
#endif