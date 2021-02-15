#include "renderfactory.h"

std::vector<Hierarchy*> RenderFactory::getAllEntityWithChildren(std::vector<Hierarchy*> _entities) {
	std::vector<Hierarchy*> entities = std::vector<Hierarchy*>();
	entities = RenderFactory::_getAllEntityWithChildren(_entities, entities);
	return entities;

}
std::vector<Hierarchy*> RenderFactory::_getAllEntityWithChildren(std::vector<Hierarchy*> _entities, std::vector<Hierarchy*> _entitiesSorted) {
	for (Hierarchy* entity : _entities) {
		_entitiesSorted.push_back(entity);
		_entitiesSorted = RenderFactory::_getAllEntityWithChildren(entity->getChildren(), _entitiesSorted);
	}

	return _entitiesSorted;
}

std::map<std::string, std::map<MeshType, std::vector<Entity*>>> RenderFactory::sortEnitiesByMaterialAndMeshType(std::vector<Hierarchy*> _entities) {
	std::map<std::string, std::map<MeshType, std::vector<Entity*>>> entities = std::map<std::string, std::map<MeshType, std::vector<Entity*>>>();
	entities = RenderFactory::_sortEnitiesByMaterialAndMeshType(_entities, entities);
	return entities;
}

std::map<std::string, std::map<MeshType, std::vector<Entity*>>> RenderFactory::_sortEnitiesByMaterialAndMeshType(std::vector<Hierarchy*> _entities, std::map<std::string, std::map<MeshType, std::vector<Entity*>>> _entitiesSorted) {

	for (Hierarchy* hierarchy : _entities) {
		Entity* entity = (Entity*)hierarchy;
		std::string name = entity->getMaterial()->getMaterialBuffer()->getName();
		MeshType type = entity->getMesh()->getType();
		_entitiesSorted[name][type].push_back(entity);
		_entitiesSorted = RenderFactory::_sortEnitiesByMaterialAndMeshType(entity->getChildren(), _entitiesSorted);
	}
	return _entitiesSorted;
}
