#ifndef ENTITY_CLASS
#define ENTITY_CLASS

#include "hierarchy.h"
#include "vector3.h"

class Entity : Hierarchy
{
public:
	Entity();
	virtual ~Entity();

	Vector3 getPostion() { return _position };
	void setPosition(Vector3 position) { _position = position; }
	float getRotation() { return _rotation; }
	void setRotation(float rotation) { _rotation = rotation; }

private:
	Vector3 _position;
	float _rotation;
	Vector3 scale = new Vector3(1, 1, 1);

};

#endif
