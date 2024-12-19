#include "Vector4.h"

// Constructor
Vector4::Vector4(float x, float y, float z, float w) : vec(x,y,z), w(w) {}
Vector4::Vector4(const Vector3& vec, float w) : vec(vec), w(w) {}

// Addition
Vector4 Vector4::operator+(const Vector4& other) const {
    return Vector4(((vec * w) + (other.vec * other.w)), 1.0);
}

// Subtraction
Vector4 Vector4::operator-(const Vector4& other) const {
    Vector4(((vec * w) - (other.vec * other.w)), 1.0);
}

// Scaling
Vector4 Vector4::operator*(const float scalar) const {
    return Vector4(vec*scalar, w);
}

// Division
Vector4 Vector4::operator/(const float scalar) const {
    return Vector4(vec*scalar, w);
}

// Compound assignment operators
Vector4& Vector4::operator+=(const Vector4& other) {
    *this = *this + other;
    return *this;
}

Vector4& Vector4::operator-=(const Vector4& other) {
    *this = *this - other;
    return *this;
}

Vector4& Vector4::operator*=(const float scalar) {
    vec *= scalar;
    return *this;
}

Vector4& Vector4::operator/=(const float scalar) {
    vec /= scalar;
    return *this;
}

// Rotation around the X-axis
Vector4 Vector4::rotationX(const Vector4& vec, float angle) {
    return Vector4(
        Vector3::rotationX(vec.vec,angle),
        vec.w
    );
}

// Rotation around the Y-axis
Vector4 Vector4::rotationY(const Vector4& vec, float angle) {
    return Vector4(
        Vector3::rotationY(vec.vec, angle),
        vec.w
    );
}

// Rotation around the Z-axis
Vector4 Vector4::rotationZ(const Vector4& vec, float angle) {
    return Vector4(
        Vector3::rotationZ(vec.vec, angle),
        vec.w
    );
}

// Scaling
Vector4 Vector4::scaling(const Vector4& vec, float sx, float sy, float sz) {
    return Vector4(
        Vector3::scaling(vec.vec, sx, sy, sz),
        vec.w
    );
}

// Translation
Vector4 Vector4::translate(const Vector4& vec, float tx, float ty, float tz) {
    return Vector4(
        Vector3::translate(vec.vec, sx, sy, sz),
        vec.w
    );
}

// Dot product
float Vector4::dot(const Vector4& v1, const Vector4& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Cross product (only makes sense for 3D vectors, so we ignore w)
Vector4 Vector4::cross(const Vector4& v1, const Vector4& v2) {
    return Vector4(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x,
        1.0f
    );
}

// Magnitude
float Vector4::length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

// Normalize
Vector4 Vector4::normalized() const {
    float len = length();
    if (len > 0) {
        return Vector4(x / len, y / len, z / len, w / len);
    }
    return Vector4();
}

// Static functions for common vectors
Vector4 Vector4::zero() {
    return Vector4(0, 0, 0, 0);
}

Vector4 Vector4::one() {
    return Vector4(1, 1, 1, 1);
}

Vector4 Vector4::unitX() {
    return Vector4(1, 0, 0, 0);
}

Vector4 Vector4::unitY() {
    return Vector4(0, 1, 0, 0);
}

Vector4 Vector4::unitZ() {
    return Vector4(0, 0, 1, 0);
}

Vector4 Vector4::unitW() {
    return Vector4(0, 0, 0, 1);
}

// Print
void Vector4::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl;
}

Vector4 operator-(const Vector4& vec) {
    return Vector4(-vec.x, -vec.y, -vec.z, vec.w);
}

// Overload stream insertion operator
std::ostream& operator<<(std::ostream& os, const Vector4& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
}

// Overload stream extraction operator for formatted input
std::istream& operator>>(std::istream& is, Vector4& vec) {
    char comma;
    if (!(is >> vec.x >> comma >> vec.y >> comma >> vec.z >> comma >> vec.w)) {
        is.setstate(std::ios::failbit);
    }
    return is;
}

// Overload stream extraction operator for string input
std::istringstream& operator>>(std::istringstream& iss, Vector4& vec) {
    char comma;
    if (!(iss >> vec.x >> comma >> vec.y >> comma >> vec.z >> comma >> vec.w)) {
        iss.setstate(std::ios::failbit);
    }
    return iss;
}
