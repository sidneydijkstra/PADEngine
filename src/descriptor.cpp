#include "descriptor.h"

Descriptor::Descriptor() {
	_layout = new DescriptorLayout();
	this->_descriptorPool = nullptr;
	this->_descriptorPoolSize = 0;
}

Descriptor::Descriptor(VkDescriptorSetLayoutBinding* _descriptorLayout, int _descriptorLayoutSize, VkDescriptorPoolSize* _descriptorPool, int _descriptorPoolSize) {
	_layout = new DescriptorLayout(_descriptorLayoutSize, _descriptorLayout);
	this->_descriptorPool = _descriptorPool;
	this->_descriptorPoolSize = _descriptorPoolSize;
}

DescriptorPool* Descriptor::getPool() {
	DescriptorPool* pool = _descriptorPool == nullptr ? new DescriptorPool() : new DescriptorPool(_descriptorPoolSize, _descriptorPool);
	_descriptorPools.push_back(pool);
	return pool;
}

void Descriptor::freePool(DescriptorPool* _pool) {
	for (std::vector<DescriptorPool*>::iterator it = _descriptorPools.begin(); it != _descriptorPools.end(); ++it) {
		if (*it == _pool) {
			delete _pool;
			it = _descriptorPools.erase(it);
			return;
		}

		if (_descriptorPools.empty())
			return;
	}
}

VkDescriptorSetLayout& Descriptor::getLayout() {
	return this->_layout->getLayout();
}

Descriptor::~Descriptor() {
	delete _layout;

	for (std::vector<DescriptorPool*>::iterator it = _descriptorPools.begin(); it != _descriptorPools.end(); ++it) {
		if (*it != NULL) {
			delete *it;
			it = _descriptorPools.erase(it);
		}
	}
}
