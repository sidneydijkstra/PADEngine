/// @file light.h
/// @brief Standalone header providing Light functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef LIGHT_CLASS
#define LIGHT_CLASS

#include "entity.h"

/// @brief Class holding Light information.
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
#endif