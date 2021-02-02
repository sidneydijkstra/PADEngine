/// @file scene.h
/// @brief Standalone header providing Scene functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef SCENE_CLASS
#define SCENE_CLASS

#include <stdlib.h>
#include <iostream>

#include "entity.h"
#include "camera.h"

/// @brief Class describing a Scene object, which stores all the information for a Scene.
class Scene : public Hierarchy {
	public:
		/// @brief The constructor for the Scene class.
		/// @param _name Name of the Scene.
		Scene(std::string _name);
		/// @brief The deconstructor for the Scene class.
		~Scene();

		/// @brief Update function of the Scene.
		virtual void update();

		/// @brief Recreate function of the Scene.
		/// @param _index Current index of SequenceManager.
		void recreate(int _index);

		/// @brief Update Scene descriptors.
		/// @param _index Current index of SequenceManager.
		/// @param _descriptorSets VkDescriptorSet to use.
		virtual void updateDescriptors(int _index, VkDescriptorSet _descriptorSets);

		/// @brief Get name of the Scene.
		/// @return Name of the Scene.
		std::string getName() { return _name; }

		/// @brief Get Camera of the Scene.
		/// @return Pointer to Camera of the Scene.
		Camera* getCamera();

		StorageBuffer<StorageBufferData>* _bufferData;
	private:
		Camera* _camera; ///< @brief Camera object pointer of Scene.
		std::string _name; ///< @brief Name of Scene.
};
#endif