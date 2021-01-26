
#ifndef RENDERFACTORY_CLASS
#define RENDERFACTORY_CLASS

#include "scene.h"
#include "hierarchy.h"

class RenderFactory {
	public:
		static std::map<MeshType, std::vector<Entity*>> sortEntitiesByMeshType(std::vector<Entity*> _entities) {
			std::map<MeshType, std::vector<Entity*>> entities = std::map<MeshType, std::vector<Entity*>>();
			
			for (Entity* entity : _entities) {
				MeshType type = entity->getMesh()->getType();
				entities[type].push_back(entity);
			}
			
			return entities;
		};

		static std::map<std::string, std::map<MeshType, std::vector<Entity*>>> sortEnitiesByMaterialAndMeshType(std::vector<Hierarchy*> _entities) {
			std::map<std::string, std::map<MeshType, std::vector<Entity*>>> entities = std::map<std::string, std::map<MeshType, std::vector<Entity*>>>();
			for (Hierarchy* hierarchy : _entities) {
				Entity* entity = (Entity*)hierarchy;
				std::string name = entity->getMaterial()->getName();
				MeshType type = entity->getMesh()->getType();
				entities[name][type].push_back(entity);
			}

			return entities;
		}
};
#endif