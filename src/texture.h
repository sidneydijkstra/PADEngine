
#ifndef TEXTURE_CLASS
#define TEXTURE_CLASS

#include "resourcemanager.h"
#include "texturebuffer.h"

class Texture {
	public:
		Texture();
		~Texture();

		void loadTexture(const char* _path);
		TextureBuffer* getBuffer();

	private:
		TextureBuffer* _buffer;
};
#endif