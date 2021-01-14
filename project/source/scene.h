#include <cstdint>


#ifndef SCENE_CLASS
#define SCENE_CLASS

#include "entity.h"

class Scene {
	public:
		Scene();
		~Scene();

		void update();
		void recreate(int _index);

		std::vector<Entity*> getChildren() {
			return _children;
		};

	private:
		std::vector<Entity*> _children;
};
#endif