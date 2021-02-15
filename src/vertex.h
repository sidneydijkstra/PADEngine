/// @file vertex.h
/// @brief Standalone header providing Vertex functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef VERTEX_CLASS
#define VERTEX_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <array>

/// @brief Struct describing a Vertex object, which contains Vertex data.
///
/// The Vertex class is used to store the data from each individual vertex within a VertexBuffer. 
/// Here the information like position, normal and the texture coordinates are stored for later use when for example building the mesh of the model or attaching the texture correctly on the model.

struct Vertex {
	glm::vec3 pos; ///< @brief Position of Vertex.
	glm::vec3 normal; ///< @brief Normal of Vertex.
	glm::vec2 texCoord; ///< @brief Texture cordinates of Vertex.

	/// @brief Function to get descriptor bindings.
	/// @return The VkVertexInputBindingDescription.
	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	/// @brief Function to get descriptor attribures.
	/// @return A std::array of VkVertexInputAttributeDescription.
	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, normal);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);


		return attributeDescriptions;
	}

	/// @brief Operator overloader for eaqals operation.
	/// @param other Other Vertex.
	/// @return Boolean of operation check.
	bool operator==(const Vertex& other) const {
		return pos == other.pos && normal == other.normal && texCoord == other.texCoord;
	}
};

namespace std {
	template<> struct hash<Vertex> {
		size_t operator()(Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^
				(hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^
				(hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}

#endif