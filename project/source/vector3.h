#ifndef PAD_ENGINE_VECTOR3_HEADER
#define PAD_ENGINE_VECTOR3_HEADER

#include <glm/vec3.hpp>

#include <cassert>
#include <cmath>
#include <random>

namespace pad {

using real = float;

struct Vector3 {

    real x, y, z;

    static Vector3 zero() noexcept;

    static Vector3 forward() noexcept;
    static Vector3 back() noexcept;

    static Vector3 up() noexcept;
    static Vector3 down() noexcept;

    static Vector3 right() noexcept;
    static Vector3 left() noexcept;

    static Vector3 positiveInfinity() noexcept;
    static Vector3 negativeInfinity() noexcept;

    static Vector3 random() noexcept;

    Vector3(real x, real y, real z) noexcept;

    Vector3() noexcept = default;
    Vector3(const Vector3&) noexcept = default;
    Vector3(Vector3&&) noexcept = default;

    const real& operator[](int n) const noexcept;
    real& operator[](int n) noexcept;

    Vector3& operator+=(const Vector3& other) noexcept;
    Vector3& operator-=(const Vector3& other) noexcept;

    Vector3& operator*=(real scalar) noexcept;
    Vector3& operator/=(real scalar) noexcept;

    operator glm::vec3() const noexcept;
    glm::vec3 glm();

    real magnitude() const noexcept;
    real magnitudeSqr() const noexcept;

    ~Vector3() noexcept = default;

};

bool operator==(const Vector3& left_vector, const Vector3& right_vector) noexcept;
bool operator!=(const Vector3& left_vector, const Vector3& right_vector) noexcept;

Vector3 operator+(Vector3 vector) noexcept;
Vector3 operator-(Vector3 vector) noexcept;

Vector3 operator+(Vector3 left_vector, const Vector3& right_vector) noexcept;
Vector3 operator-(Vector3 left_vector, const Vector3& right_vector) noexcept;

Vector3 operator*(Vector3 vector, real scalar) noexcept;
Vector3 operator*(real scalar, Vector3 vector) noexcept;
Vector3 operator/(Vector3 vector, real scalar) noexcept;

real abs(const Vector3& vector) noexcept;

Vector3 normalize(Vector3 vector) noexcept;
Vector3 limit(Vector3 vector, real max_magnitude) noexcept;

Vector3 lerp(const Vector3& start_vector, const Vector3& end_vector, real factor) noexcept;
Vector3 moveTowards(const Vector3& start_vector, const Vector3& end_vector, real max_delta) noexcept;

real angle(const Vector3& left_vector, const Vector3& right_vector) noexcept;
real distance(const Vector3& start_vector, const Vector3& end_vector) noexcept;

real dot(const Vector3& left_vector, const Vector3& right_vector) noexcept;
Vector3 cross(const Vector3& left_vector, const Vector3& right_vector) noexcept;

/* * * * * * * * *
* Implementation *
* * * * * * * * */ 

namespace detail {

inline static constexpr auto epsilon = 0.000001;

inline bool equals(const real a, const real b, const real epsilon = detail::epsilon) noexcept {
    return fabs(a-b) <= epsilon;
}

inline int compare(const real a, const real b, const real epsilon = detail::epsilon) noexcept {
    return (a-b < -epsilon) ? -1 :
           (a-b > +epsilon) ? +1 : 0;
}

}

inline Vector3 Vector3::zero() noexcept {
    return Vector3{ 0,  0,  0};
}

inline Vector3 Vector3::forward() noexcept {
    return Vector3{ 0,  0, +1};
}

inline Vector3 Vector3::back() noexcept {
    return Vector3{ 0,  0, -1};
}

inline Vector3 Vector3::up() noexcept {
    return Vector3{ 0, +1,  0};
}

inline Vector3 Vector3::down() noexcept {
    return Vector3{ 0, -1,  0};
}

inline Vector3 Vector3::right() noexcept {
    return Vector3{+1,  0,  0};
}

inline Vector3 Vector3::left() noexcept {
    return Vector3{-1,  0,  0};
}

inline Vector3 Vector3::positiveInfinity() noexcept {
    static_assert(std::numeric_limits<real>::is_iec559, "Floating point numbers on your platform are not capable of representing infinite values!");
    return Vector3{+INFINITY, +INFINITY, +INFINITY};
}

inline Vector3 Vector3::negativeInfinity() noexcept {
    static_assert(std::numeric_limits<real>::is_iec559, "Floating point numbers on your platform are not capable of representing infinite values!");
    return Vector3{-INFINITY, -INFINITY, -INFINITY};
}

inline Vector3 Vector3::random() noexcept {
    static std::random_device seeder{};
    static std::mt19937 generator{seeder()};
    static std::uniform_real_distribution<real> distributor{-1.0, +1.0};
    
    Vector3 result{
        distributor(generator),
        distributor(generator),
        distributor(generator)
    };

    result /= result.magnitude();

    return result;
}

inline Vector3::Vector3(real x, real y, real z) noexcept : x(x), y(y), z(z) {
    // Empty.
}

inline const real& Vector3::operator[](const int n) const noexcept {
    assert((0<=n && n<=2) && "The index 'n' is out of range!");
    return reinterpret_cast<const real(&)[3]>(*this)[n];
}

inline real& Vector3::operator[](const int n) noexcept {
    assert((0<=n && n<=2) && "The index 'n' is out of range!");
    return reinterpret_cast<real(&)[3]>(*this)[n];
}

inline Vector3& Vector3::operator+=(const Vector3& other) noexcept {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& other) noexcept {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;

    return *this;
}

inline Vector3& Vector3::operator*=(const real scalar) noexcept {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;

    return *this;
}

inline Vector3& Vector3::operator/=(const real scalar) noexcept {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;

    return *this;
}

inline Vector3::operator glm::vec3() const noexcept {
    return glm::vec3(x, y, z);
}

inline glm::vec3 Vector3::glm() {
	return glm::vec3(x, y, z);
}

inline real Vector3::magnitude() const noexcept {
    return sqrt(x*x + y*y + z*z);
}

inline real Vector3::magnitudeSqr() const noexcept {
    return (x*x + y*y + z*z);
}

inline bool operator==(const Vector3& left_vector, const Vector3& right_vector) noexcept {
    return (detail::equals(left_vector.x, right_vector.x) &&
            detail::equals(left_vector.y, right_vector.y) && detail::equals(left_vector.z, right_vector.z));
}

inline bool operator!=(const Vector3& left_vector, const Vector3& right_vector) noexcept {
    return !(left_vector==right_vector);
}

inline Vector3 operator+(Vector3 vector) noexcept {
    vector.x = +vector.x;
    vector.y = +vector.y;
    vector.z = +vector.z;

    return vector;
}

inline Vector3 operator-(Vector3 vector) noexcept {
    vector.x = -vector.x;
    vector.y = -vector.y;
    vector.z = -vector.z;

    return vector;
}

inline Vector3 operator+(Vector3 left_vector, const Vector3& right_vector) noexcept {
    left_vector += right_vector;
    return left_vector;
}

inline Vector3 operator-(Vector3 left_vector, const Vector3& right_vector) noexcept {
    left_vector -= right_vector;
    return left_vector;
}

inline Vector3 operator*(Vector3 vector, const real scalar) noexcept {
    vector *= scalar;
    return vector;
}

inline Vector3 operator*(const real scalar, Vector3 vector) noexcept {
    return vector * scalar;
}

inline Vector3 operator/(Vector3 vector, const real scalar) noexcept {
    vector /= scalar;
    return vector;
}

inline real abs(const Vector3& vector) noexcept {
    return vector.magnitude();
}

inline Vector3 normalize(Vector3 vector) noexcept {
    vector /= vector.magnitude();
    return vector;
}

inline Vector3 limit(Vector3 vector, const real max_magnitude) noexcept {
    assert((max_magnitude >= 0.0) && "The parameter 'max_magnitude' must be positive!");
    return detail::compare(vector.magnitudeSqr(), (max_magnitude*max_magnitude)) == 1 ? normalize(vector)*max_magnitude : vector;
}

inline Vector3 lerp(const Vector3& start_vector, const Vector3& end_vector, const real factor) noexcept {
    assert((0.0<=factor && factor<=1.0) && "The parameter 'factor' must be between 0.0 and 1.0!");
    return ((1-factor)*start_vector + factor*end_vector);
}

inline Vector3 moveTowards(const Vector3& start_vector, const Vector3& end_vector, const real max_delta) noexcept {
    return start_vector + limit(end_vector-start_vector, max_delta);
}

inline real angle(const Vector3& left_vector, const Vector3& right_vector) noexcept {
    return acos(dot(left_vector, right_vector) / (abs(left_vector)*abs(right_vector)));
}

inline real distance(const Vector3& start_vector, const Vector3& end_vector) noexcept {
    return abs(start_vector - end_vector);
}

inline real dot(const Vector3& left_vector, const Vector3& right_vector) noexcept {
    return (left_vector.x*right_vector.x + left_vector.y*right_vector.y + left_vector.z*right_vector.z);
}

inline Vector3 cross(const Vector3& left_vector, const Vector3& right_vector) noexcept {
    return Vector3{
        left_vector.y*right_vector.z - left_vector.z*right_vector.y,
        left_vector.z*right_vector.x - left_vector.x*right_vector.z,
        left_vector.x*right_vector.y - left_vector.y*right_vector.x
    };
}

}

/* Temporary using-directive. Remove when the whole engine uses the same namespace. */
using namespace pad;

#endif
