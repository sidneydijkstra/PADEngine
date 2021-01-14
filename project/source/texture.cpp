#include "texture.h"

Texture::Texture() {
	_buffer = ResourceManager::getInstance()->getTextureBuffer("assets/logo.png");
}

void Texture::loadTexture(const char* _path) {
	_buffer = ResourceManager::getInstance()->getTextureBuffer(_path);
}

TextureBuffer* Texture::getBuffer() {
	return _buffer;
}

Texture::~Texture() {
}
