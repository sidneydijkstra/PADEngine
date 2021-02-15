/// @file material.h
/// @brief Standalone header providing Material functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021


#ifndef MATERIAL_CLASS
#define MATERIAL_CLASS

#include "materialmanager.h"
#include "materialbuffer.h"
#include "uniformbuffer.h"
#include "color.h"
#include "vector3.h"

#include <cstdint>
#include <iostream>

namespace pad {

/// @brief Class holding Material.
///
/// The material class contains information about the material that can be attached to the Entity object. 
/// Here the data needed for the material like its texture, color and shine are stored which can later be used to load the material on to an Entity object within a Scene.

class Material {
	public:
		/// @brief The constructor for the Material class.
		Material(const char* = "mat_normal_PBR");
		/// @brief The deconstructor for the Material class.
		~Material();

		/// @brief Function to get the current VkDescriptorPool in use.
		/// @return Reference to VkDescriptorPool in use.
		VkDescriptorPool& getPool();

		/// @brief Function to get the current MaterialBuffer pointer in use.
		/// @return Pointer to MaterialBuffer in use.
		MaterialBuffer* getMaterialBuffer();

		/// @brief Function to get the current UniformBuffer<MaterialBufferObject> pointer in use.
		/// @return Pointer to UniformBuffer<MaterialBufferObject> in use.
		UniformBuffer<MaterialBufferObject>* getMaterialUniformBuffer();

		/// @brief Function to set Material to use.
		/// @param _name Name of Material.
		void setMaterial(const char* _name);

		/// @brief Get current VkDescriptorSet, final buffers for storing entity data.
		/// @param _index Current index.
		/// @return Reference of VkDescriptorSet.
		void updateDescriptors(int _index, VkDescriptorSet _descriptorSet);

		Color color; ///< @brief Color of Material.
		Vector3 ambient; ///< @brief Ambient of Material.
		Vector3 diffuse; ///< @brief Diffuse of Material.
		Vector3 specular; ///< @brief Specular of Material.
		float shininess; ///< @brief Shininess of Material.
	private:
		DescriptorPool* _pool;
		MaterialBuffer* _buffer;
		UniformBuffer<MaterialBufferObject>* _bufferObject;

		void setup(const char* _name);
};

}

#endif