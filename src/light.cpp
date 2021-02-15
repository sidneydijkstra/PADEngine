#include "light.h"

namespace pad {

Light::Light() : Entity() {
	this->_type = EntityType::LIGHT;
	this->_lightBuffer = new UniformBuffer<LightBufferObject>();
	this->scale = Vector3(0.1,0.1,0.1);
}

Light::~Light() {
	delete _lightBuffer;
}

UniformBuffer<LightBufferObject>* Light::getLightBuffer() {
	return this->_lightBuffer;
}

}
