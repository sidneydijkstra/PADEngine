/// @file vector3.h
/// @brief Standalone header providing Vector3 functionality.
/// @author Sander Albers, Sidney Dijkstra, Naomi Poort
/// @version 1.0.0
/// @date 30/01/2021

#ifndef PAD_ENGINE_VECTOR3_HEADER
#define PAD_ENGINE_VECTOR3_HEADER

#include <glm/vec3.hpp>

#include <cassert>
#include <cmath>
#include <random>

namespace pad {

using real = float;

/// @brief Struct describing a 3-dimensional vector.
struct Vector3 {

    real x, y, z;

    /// @brief Creates a Vector3 pointing to the origin.
    /// @return A Vector3 object initialized as {0, 0, 0}.
    static Vector3 zero() noexcept;
    
    /// @brief Creates a Vector3 pointing forward.
    /// @return A Vector3 object initialized as {0, 0, 1}.
    static Vector3 forward() noexcept;
    
    /// @brief Creates a Vector3 pointing back.
    /// @return A Vector3 object initialized as {0, 0, -1}.
    static Vector3 back() noexcept;

    /// @brief Creates a Vector3 pointing up.
    /// @return A Vector3 object initialized as {0, 1, 0}.
    static Vector3 up() noexcept;

    /// @brief Creates a Vector3 pointing down.
    /// @return A Vector3 object initialized as {0, -1, 0}.
    static Vector3 down() noexcept;

    /// @brief Creates a Vector3 pointing to the right.
    /// @return A Vector3 object initialized as {1, 0, 0}.
    static Vector3 right() noexcept;

    /// @brief Creates a Vector3 pointing to the left.
    /// @return A Vector3 object initialized as {-1, 0, 0}.
    static Vector3 left() noexcept;

    /// @brief Creates a Vector3 pointing towards positive infinity.
    /// @return A Vector3 object initialized as {INF, INF, INF}.
    static Vector3 positiveInfinity() noexcept;

    /// @brief Creates a Vector3 pointing towards negative infinity.
    /// @return A Vector3 object initialized as {-INF, -INF, -INF}.
    static Vector3 negativeInfinity() noexcept;

    /// @brief Creates a Vector3 pointing in a random direction, with a magnitude of 1.
    /// @return A Vector3 object with random coordinates in the range [-1, +1] with a magnitude of 1.
    static Vector3 random() noexcept;

    /// @brief Constructs a new Vector3 object with the given coordinates.
    /// @param x The value of the x-coordinate.
    /// @param y The value of the y-coordinate.
    /// @param z The value of the z-coordinate.
    /// @return A Vector3 object with the given coordinates.
    Vector3(real x, real y, real z) noexcept;

    Vector3() noexcept = default;
    Vector3(const Vector3&) noexcept = default;
    Vector3(Vector3&&) noexcept = default;

    Vector3& operator=(const Vector3&) noexcept = default;
    Vector3& operator=(Vector3&&) noexcept = default;

    /// @brief Gets the element at position 'n' of the Vector3 object.
    /// @param n The index of the element to retrieve, must be either 0 (for x), 1 (for y), or 2 (for z).
    /// @return A const reference to the x-coordinate if n equals 0, the y-coordinate if n equals 1 or the z-coordinate if n equals 2.
    const real& operator[](int n) const noexcept;

    /// @brief Gets the element at position 'n' of the Vector3 object.
    /// @param n The index of the element to retrieve, must be either 0 (for x), 1 (for y), or 2 (for z).
    /// @return A reference to the x-coordinate if n equals 0, the y-coordinate if n equals 1 or the z-coordinate if n equals 2.
    real& operator[](int n) noexcept;

    /// @brief Adds another Vector3 to this Vector3 object.
    /// @param other The vector to add to this vector.
    /// @return A reference to the Vector3 object that was added to.
    Vector3& operator+=(const Vector3& other) noexcept;

    /// @brief Subtracts another Vector3 from this Vector3 object.
    /// @param other The vector to subtract from this vector.
    /// @return A reference to the Vector3 object that was subtracted from.
    Vector3& operator-=(const Vector3& other) noexcept;

    /// @brief Multiplies this Vector3 object by the given number.
    /// @param scalar The amount by which to multiply this vector.
    /// @return A reference to the Vector3 object that was multiplied.
    Vector3& operator*=(real scalar) noexcept;

    /// @brief Divides this Vector3 object by the given number.
    /// @param scalar The amount by which to divide this vector.
    /// @return A reference to the Vector3 object that was divided.
    Vector3& operator/=(real scalar) noexcept;

    /// @brief Converts this Vector3 object to a glm::vec3 object.
    /// @return This vector as a glm::vec3 object.
    operator glm::vec3() const noexcept;

    /// @brief Converts this Vector3 object to a glm::vec3 object.
    /// @return This vector as a glm::vec3 object.
    glm::vec3 glm();

    /// @brief Gets the magnitude of the Vector3 object.
    /// @return The magnitude, also known as the length, of the vector.
    real magnitude() const noexcept;

    /// @brief Gets the squared magnitude of the Vector3 object.
    ///
    /// Almost the same as <tt>Vector3::magnitude</tt> except the more expensive square root operation is not applied;
    /// thus giving a value that is 'n' times as large as the magnitude, where 'n' equals the magnitude itself.
    /// 
    /// This method may be used where the actual value of the magnitude doesn't really matter, but where you do still need
    /// to compare the length(s) of one or more vectors; or when you need the squared magnitude for a calculation. As this
    /// method avoids taking the square root, which is an expensive operation, using this method might improve performance.
    /// 
    /// @return The squared magnitude of the vector.
    real magnitudeSqr() const noexcept;

    ~Vector3() noexcept = default;

};

/// @brief Compares two vector to each other for equality.
/// @param left_vector The Vector3 object to the left of the equality operator.
/// @param right_vector The Vector3 object to the right of the equality operator.
/// @return True if both vectors are (roughly) equal, false otherwise.
bool operator==(const Vector3& left_vector, const Vector3& right_vector) noexcept;

/// @brief Compares two vector to each other inequality.
/// @param left_vector The Vector3 object to the left of the inequality operator.
/// @param right_vector The Vector3 object to the right of the inequality operator.
/// @return True if both vectors are (roughly) inequal, false otherwise.
bool operator!=(const Vector3& left_vector, const Vector3& right_vector) noexcept;

/// @brief Unary plus operator, essentially the same as '<tt>Vector3::zero()</tt> + vector'.
///
/// This operator has no effect on its input and exists mostly as an antagonist to
/// the unary minus operator, which has a more interesting effect on its input.
/// 
/// @param vector The Vector3 object this operator was applied to.
/// @return A Vector3 object equal to the input.
Vector3 operator+(Vector3 vector) noexcept;

/// @brief Unary minus operator, essentially the same as '<tt>Vector3::zero()</tt> - vector'.
///
/// As this operator is the same as '<tt>Vector3::zero()</tt> - vector', the output will be
/// a vector of the same length of the input, but pointing in the opposite direction.
/// 
/// @param vector The Vector3 object this operator was applied to.
/// @return A Vector3 object equal to the inverse of the input.
Vector3 operator-(Vector3 vector) noexcept;

/// @brief Adds two vectors to each other.
/// @param left_vector The Vector3 object to the left of the addition operator.
/// @param right_vector The Vector3 object to the right of the addition operator.
/// @return A Vector3 object equal to the sum of the given vectors.
Vector3 operator+(Vector3 left_vector, const Vector3& right_vector) noexcept;

/// @brief Subtracts two vectors from each other.
/// @param left_vector The Vector3 object to the left of the subtraction operator.
/// @param right_vector The Vector3 object to the right of the subtraction operator.
/// @return A Vector3 object equal to the difference of the given vectors.
Vector3 operator-(Vector3 left_vector, const Vector3& right_vector) noexcept;

/// @brief Multiplies a vector by a scalar.
/// @param vector The Vector3 object to the left of the multiplication operator.
/// @param scalar The <tt>real</tt> number to the right of the multiplication operator.
/// @return A Vector3 object equal to <p>vector</p> multiplied by <p>scalar</p>.
Vector3 operator*(Vector3 vector, real scalar) noexcept;

/// @brief Multiplies a vector by a scalar.
/// @param scalar The <tt>real</tt> number to the left of the multiplication operator.
/// @param vector The Vector3 object to the right of the multiplication operator.
/// @return A Vector3 object equal to <p>vector</p> multiplied by <p>scalar</p>.
Vector3 operator*(real scalar, Vector3 vector) noexcept;

/// @brief Divides a vector by a scalar.
/// @param vector The Vector3 object to the left of the division operator.
/// @param scalar The <tt>real</tt> number to the right of the division operator.
/// @return A Vector3 object equal to <p>vector</p> divided by <p>scalar</p>.
Vector3 operator/(Vector3 vector, real scalar) noexcept;

/// @brief Gets the absolute value of a vector, same as <tt>Vector3::magnitude()</tt>
/// @param vector The Vector3 object to get the absolute value of.
/// @return The absolute value (also length or magnitude) of the given vector.
real abs(const Vector3& vector) noexcept;

/// @brief Divides a vector by its magnitude.
/// @param vector The vector to normalize.
/// @return The normalized vector of the given vector.
Vector3 normalize(Vector3 vector) noexcept;

/// @brief Limits the length of a given vector by <p>max_magnitude</p>
/// @param vector The vector to limit the length of.
/// @param max_magnitude The magnitude to limit the length of <p>vector</p> to.
/// @return A vector that is at most <p>max_magnitude</p> in length, pointing in the same direction as <p>vector</p>
Vector3 limit(Vector3 vector, real max_magnitude) noexcept;

/// @brief Linearly interpolates between the given vectors.
///
/// Essentially moves the first vector towards the second, by a percentage given by the parameter <p>factor</p>.
/// 
/// @param start_vector The vector to move from.
/// @param end_vector The vector to move towards.
/// @param factor A percentage given as floating point number in the range 0.0 (0%) to 1.0 (100%).
/// @return A vector equal to <tt>start_vector + factor*(end_vector-start_vector)</tt>
Vector3 lerp(const Vector3& start_vector, const Vector3& end_vector, real factor) noexcept;

/// @brief Moves the first vector towards the second, moving at most <p>max_delta</p>.
///
/// Almost the same as <tt>lerp</tt>, except instead of moving by a percentage, you move by fixed number until
/// you've reached the </p>end_vector<p>. 
/// 
/// @param start_vector The vector to move from.
/// @param end_vector The vector to move towards.
/// @param max_delta The maximum distance that may be mvoed from <p>start_vector</p> to <p>end_vector</p>.
/// @return A vector equal to <tt>start_vector + factor*(end_vector-start_vector)</tt>
Vector3 moveTowards(const Vector3& start_vector, const Vector3& end_vector, real max_delta) noexcept;

/// @brief Calculates the angle between two given vectors.
/// @param left_vector One of the vectors to calculate the angle between.
/// @param right_vector One of the vectors to calculate the angle between. 
/// @return The angle between the two given vectors in radians.
real angle(const Vector3& left_vector, const Vector3& right_vector) noexcept;

/// @brief Calculates the distance between two given vectors.
/// @param start_vector The start point.
/// @param end_vector The end point.
/// @return The distance between <p>start_vector</p> and <p>end_vector</p>.
real distance(const Vector3& start_vector, const Vector3& end_vector) noexcept;

/// @brief Calculates the dot product of the given vectors.
/// @param left_vector The vector that would appear to the left of the dot operator.
/// @param right_vector The vector that would appear to the right of the dot operator.
/// @return The dot product of the given vectors.
real dot(const Vector3& left_vector, const Vector3& right_vector) noexcept;

/// @brief Calculates the cross product of the given vectors.
/// @param left_vector The vector that would appear to the left of the cross operator.
/// @param right_vector The vector that would appear to the right of the cross operator.
/// @return The cross product of the given vectors.
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

#endif
