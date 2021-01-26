
#ifndef SCENE_CLASS
#define SCENE_CLASS

#include <stdlib.h>

#include "entity.h"
#include "camera.h"

class Scene : public Hierarchy {
	public:
		Scene();
		~Scene();

		virtual void update();
		void recreate(int _index);

		Camera* getCamera();

	private:
		Camera* _camera;
};
#endif