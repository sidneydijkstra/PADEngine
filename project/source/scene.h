
#ifndef SCENE_CLASS
#define SCENE_CLASS

#include <stdlib.h>

#include "entity.h"
#include "camera.h"

class Scene {
	public:
		Scene();
		~Scene();

		void update();
		void recreate(int _index);

		std::vector<Entity*> children() { return _children; }
		Camera* camera() { return _camera; }
		string name() { return _name; }

	private:
		std::vector<Entity*> _children;
		Camera* _camera;
		string _name;
};
#endif