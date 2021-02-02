/// @file texturebuffer.h
/// @brief Standalone header providing TextureBuffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef TEXTUREBUFFER_CLASS
#define TEXTUREBUFFER_CLASS

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "imagebuffer.h"

#include <iostream>
#include <vector>
#include <string>
#include <array>

/// @brief Struct for texture buffer data.
struct TextureBufferData {
	VkImageView textureImageView;
	VkSampler textureSampler;
};

/// @brief Class describing a TextureBuffer object, which stores all the buffers for an texture.
class TextureBuffer : ImageBuffer {
public:
	/// @brief The constructor for the TextureBuffer class.
	/// @param _path Path to texture file.
	TextureBuffer(const char* _path);
	/// @brief The deconstructor for the TextureBuffer class.
	~TextureBuffer();

	/// @brief Get Texture image.
	/// @return The VkImage.
	VkImage getImage();

	/// @brief Get Texture image memory.
	/// @return The VkDeviceMemory.
	VkDeviceMemory getImageMemory();

	/// @brief Get Texture image view.
	/// @return The VkImageView.
	VkImageView getImageView();

	/// @brief Get Texture sampler.
	/// @return The VkSampler.
	VkSampler getSampler();

	/// @brief Update descriptor set.
	/// @return _index Current index of SequenceManager.
	/// @return _descriptor VkDescriptorSet to use.
	/// @return _dstBinding Index to bind buffer to.
	void updateDescriptor(int _index, VkDescriptorSet _descriptor, int _dstBinding);
private:
	VkImage _textureImage; ///< @brief VkImage of TextureBuffer.
	VkDeviceMemory _textureImageMemory; ///< @brief VkDeviceMemory of TextureBuffer.
	VkImageView _textureImageView; ///< @brief VkImageView of TextureBuffer.
	VkSampler _textureSampler; ///< @brief VkSampler of TextureBuffer.

	/// @brief Create a texture image.
	/// @param _path Path to texture file.
	void createTextureImage(const char* _path);

	/// @brief Create a texture image view.
	void createTextureImageView();

	/// @brief Create a texture sampler.
	void createTextureSampler();
};
#endif