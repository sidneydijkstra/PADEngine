/// @file texture.h
/// @brief Standalone header providing Texture functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef TEXTURE_CLASS
#define TEXTURE_CLASS

#include "resourcemanager.h"
#include "texturebuffer.h"

/// @brief Class describing a Texture object, which stores a pointer to the TextureBuffer.
///
/// This class holds the texture information which are used to render the texture on the Material, which in turn is rendered on a specific Entity object.
class Texture {
	public:
		/// @brief The constructor for the Texture class.
		Texture();
		/// @brief The deconstructor for the Texture class.
		~Texture();

		/// @brief Load a texture by path.
		/// @param _path Path to texture.
		void loadTexture(const char* _path);

		/// @brief Get the TextureBuffer pointer.
		/// @return The TextureBuffer pointer.
		TextureBuffer* getBuffer();

	private:
		TextureBuffer* _buffer; ///< @brief TextureBuffer pointer of Texture.
};
#endif