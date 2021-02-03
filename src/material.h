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

/// @brief Class holding Material.
class Material {
	public:
		Material(const char* = "mat_normal_PBR");
		~Material();

		VkDescriptorPool& getPool();
		MaterialBuffer* getMaterialBuffer();
		UniformBuffer<MaterialBufferObject>* getMaterialUniformBuffer();

		void setMaterial(const char* _name);

		void updateDescriptors(int _index, VkDescriptorSet _descriptorSet);

		Color color;
		Vector3 ambient;
		Vector3 diffuse;
		Vector3 specular;
		float shininess;
	private:
		DescriptorPool* _pool; ///< @brief DescriptorPool object pointer of Entity.
		MaterialBuffer* _buffer;
		UniformBuffer<MaterialBufferObject>* _bufferObject;

		void setup(const char* _name);
};
#endif