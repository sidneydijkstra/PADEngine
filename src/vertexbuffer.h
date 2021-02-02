/// @file vertexbuffer.h
/// @brief Standalone header providing VertexBuffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef VERTEXBUFFER_CLASS
#define VERTEXBUFFER_CLASS

#include "buffer.h"
#include "vertex.h"

#include <iostream>
#include <vector>
#include <string>

/// @brief Class describing a VertexBuffer object, which stores all the Vertex data.
class VertexBuffer : Buffer {
public:
	/// @brief The constructor for the VertexBuffer class.
	/// @param _vertices A std::vector of Vertex objects.
	VertexBuffer(const std::vector<Vertex> _vertices);
	/// @brief The deconstructor for the VertexBuffer class.
	~VertexBuffer();

	/// @brief Get vertex buffer.
	/// @return The VkBuffer.
	VkBuffer getBuffer();

	/// @brief Get vertex buffer size.
	/// @return The buffer size.
	uint32_t getBufferSize();

private:
	VkBuffer _vertexBuffer; ///< @brief VkBuffer of VertexBuffer.
	VkDeviceMemory _vertexBufferMemory; ///< @brief VkDeviceMemory of VertexBuffer.
	uint32_t _vertexSize; ///< @brief Size of buffer.

	/// @brief Setup the buffer object.
	/// @param _vertices A std::vector of Vertex objects.
	void setupBuffer(const std::vector<Vertex> _vertices);

};
#endif