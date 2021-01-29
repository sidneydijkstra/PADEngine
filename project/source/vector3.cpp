#include "vector3.h"

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

glm::vec3 Vector3::glm() {
	return glm::vec3(x, y, z);
}

Vector3::operator glm::vec3() const {
	return glm::vec3(x, y, z);
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3 Vector3::operator*(const float rhs) const
{
	return Vector3(x * rhs, y * rhs, z *rhs);
}

Vector3 Vector3::operator/(const float rhs) const
{
	return Vector3(x / rhs, y / rhs, z /rhs);
}

Vector3::~Vector3() {

}