#include "hierarchy.h"

Hierarchy::Hierarchy() {
	_nextGuid = 0;
	guid = _nextGuid;
	_nextGuid++;

	_parent = NULL;
}

Hierarchy::~Hierarchy() {

}

void Hierarchy::addChild(Hierarchy* _child) {
	if (_child->_parent != NULL) {
		_child->_parent->removeChild(_child);
	}
	_child->_parent = this;
	this->_children.push_back(_child);
}

void Hierarchy::removeChild(Hierarchy* child)
{
	std::vector<Hierarchy*>::iterator it = _children.begin();
	while (it != _children.end()) {
		if ((*it)->guid == child->guid) {
			it = _children.erase(it);
		}
		else {
			++it;
		}
	}
	child->_parent = NULL;
}
