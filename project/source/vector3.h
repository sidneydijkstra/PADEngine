#ifndef ENTITY_CLASS
#define ENTITY_CLASS

class Vector3 {
public:
	Vector3(float x, float y, float z);
	Vector3();
	~Vector3();

private:
	float x, y, z = 0;

	Vector3& operator+=(const Vector3& rhs);
	Vector3 operator+(const Vector3& rhs) const;
	Vector3 operator*(const float rhs) const;
	Vector3 operator/(const float rhs) const;
	Vector3& operator-=(const Vector3& rhs);
};
#endif
