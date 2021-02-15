/// @file light.h
/// @brief Standalone header providing Light functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef LIGHT_CLASS
#define LIGHT_CLASS

#include "entity.h"

namespace pad {

/// @brief Class holding Light information.
///
/// The Light class creates a light for the scene to create a more realistic scene. 
/// Shadows are created by the light which can give a scene more depth.

class Light : public Entity {
	public:
		/// @brief The constructor for the Light class.
		Light();
		/// @brief The deconstructor for the Light class.
		~Light();

		/// @brief Get the buffer for Light.
		/// @return Pointer to light buffer.
		UniformBuffer<LightBufferObject>* getLightBuffer();

	private:
		UniformBuffer<LightBufferObject>* _lightBuffer;
};

}

#endif