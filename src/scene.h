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
#include "light.h"
#include "camera.h"

/// @brief Class describing a Scene object, which stores all the information for a Scene. Contains all of the geometry of a particular scene. They are useful for representing translations, rotations and scales (along with other affine transformations) of objects relative to each other.
class Scene : public Hierarchy {
	public:
		/// @brief The constructor for the Scene class. Here the Scene is initialized along with a new Camera and light object.
		/// @param _name Name of the Scene.
		/// @param type The Type of camera, can be set to either Orthographic or Perspective.
		Scene(std::string _name, PerspectiveType type = PerspectiveType::PERSPECTIVE);
		/// @brief The deconstructor for the Scene class.
		~Scene();

		/// @brief Update function of the Scene.
		virtual void update();

		/// @brief Recreate function of the Scene.
		/// @param _index Current index of SequenceManager.
		void recreate(int _index);

		/// @brief Update Scene descriptors.
		/// @param _index Current index of SequenceManager.
		/// @param _entity Entity to update descrptors from.
		virtual void updateDescriptors(int _index, Entity* _entity);

		/// @brief Get name of the Scene.
		/// @return Name of the Scene.
		std::string getName() { return _name; }

		/// @brief Get Camera of the Scene.
		/// @return Pointer to Camera of the Scene.
		Camera* getCamera();

	protected:
		Light* _light;

	private:
		Camera* _camera; ///< @brief Camera object pointer of Scene.
		std::string _name; ///< @brief Name of Scene.
};
#endif