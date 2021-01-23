#ifndef VECTOR3_CLASS
#define VECTOR3_CLASS

class Vector3 {
public:
	Vector3(float x, float y, float z);
	Vector3();
	~Vector3();

	float x, y, z = 0;
private:

	Vector3& operator+=(const Vector3& rhs);
	Vector3 operator+(const Vector3& rhs) const;
	Vector3 operator*(const float rhs) const;
	Vector3 operator/(const float rhs) const;
	Vector3& operator-=(const Vector3& rhs);
};
#endif
