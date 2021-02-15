/// @file indexbuffer.h
/// @brief Standalone header providing IndexBuffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef INDEXBUFFER_CLASS
#define INDEXBUFFER_CLASS

#include "buffer.h"

#include <iostream>
#include <vector>
#include <string>

/// @brief Class describing a IndexBuffer object, which stores all index/indices information of a Vertex.
///
/// The IndexBuffer is an extension of the Buffer class. This object is for storing the indices in memory. 
/// Indices determine the order in which the vertexes are drawn, for more information on the Vertex object see the Vertex class.

class IndexBuffer : Buffer {
public:
	/// @brief The constructor for the IndexBuffer class.
	/// @param _indices Indices to create the buffer with.
	IndexBuffer(std::vector<uint32_t> _indices);
	/// @brief The dedeconstructor for the IndexBuffer class.
	~IndexBuffer();

	/// @brief Get VkBuffer containing indices buffer.
	/// @return VkBuffer object.
	VkBuffer getBuffer();

	/// @brief Get size of buffer.
	/// @return Size of buffer.
	uint32_t getBufferSize();

private:
	VkBuffer _indexBuffer; ///< @brief VkBuffer object of Entity.
	VkDeviceMemory _indexBufferMemory; ///< @brief VkDeviceMemory object of Entity.
	uint32_t _indexSize; ///< @brief Index size object of Entity.

	/// @brief Setup index buffer.
	/// @param _indices Indices to create the buffer with.
	void setupBuffer(std::vector<uint32_t> _indices);
};
#endif