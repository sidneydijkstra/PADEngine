/// @file renderfactory.h
/// @brief Standalone header providing RenderFactory functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef RENDERFACTORY_CLASS
#define RENDERFACTORY_CLASS

#include "scene.h"
#include "hierarchy.h"

/// @brief Class describing a RenderFactory, which contains static function used by the Renderer.
class RenderFactory {
	public:
		/// @brief Function to sort a list of Entity pointers by MeshType.
		/// @param _entities A std::vector of Entity pointers.
		/// @return A std::map of Entity pointers arranged by MeshType.
		static std::vector<Hierarchy*> getAllEntityWithChildren(std::vector<Hierarchy*> _entities);

		/// @brief Function to sort a list of Entity pointers by MeshType and Material.
		/// @param _entities A std::vector of Entity pointers.
		/// @return A std::map of Entity pointers arranged by MeshType in a std::map arranged by Material.
		static std::map<std::string, std::map<MeshType, std::vector<Entity*>>> sortEnitiesByMaterialAndMeshType(std::vector<Hierarchy*> _entities);

	private:
		static std::vector<Hierarchy*> _getAllEntityWithChildren(std::vector<Hierarchy*> _entities, std::vector<Hierarchy*> _entitiesSorted);
		static std::map<std::string, std::map<MeshType, std::vector<Entity*>>> _sortEnitiesByMaterialAndMeshType(std::vector<Hierarchy*> _entities, std::map<std::string, std::map<MeshType, std::vector<Entity*>>> _entitiesSorted);
};
#endif