#ifndef VECTOR3_CLASS
#define VECTOR3_CLASS

#include <glm/vec3.hpp>

class Vector3 {
public:
	Vector3(float x, float y, float z);
	Vector3();
	~Vector3();

	glm::vec3 glm();

	operator glm::vec3() const;

	float x, y, z = 0;
private:

	Vector3& operator+=(const Vector3& rhs);
	Vector3 operator+(const Vector3& rhs) const;
	Vector3 operator*(const float rhs) const;
	Vector3 operator/(const float rhs) const;
	Vector3& operator-=(const Vector3& rhs);
};
#endif
