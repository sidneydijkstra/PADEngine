#include "texture.h"

namespace pad {

Texture::Texture() {
	_buffer = ResourceManager::getInstance()->getTextureBuffer("assets/white.png");
}

void Texture::loadTexture(const char* _path) {
	_buffer = ResourceManager::getInstance()->getTextureBuffer(_path);
}

TextureBuffer* Texture::getBuffer() {
	return _buffer;
}

Texture::~Texture() {
}

}