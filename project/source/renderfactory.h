
#ifndef RENDERFACTORY_CLASS
#define RENDERFACTORY_CLASS

#include "scene.h"
#include "entity.h"

class RenderFactory {
	public:
		static std::map<MeshType, std::vector<Entity*>> sortEntitiesByMeshType(std::vector<Entity*> _entities) {
			std::map<MeshType, std::vector<Entity*>> entities = std::map<MeshType, std::vector<Entity*>>();
			
			for (Entity* entity : _entities) {
				MeshType type = entity->mesh()->getType();
				entities[type].push_back(entity);
			}
			
			return entities;
		};
};
#endif