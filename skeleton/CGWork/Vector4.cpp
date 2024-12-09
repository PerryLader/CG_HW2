#include "Vector4.h"

// Constructor
Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

// Addition
Vector4 Vector4::operator+(const Vector4& other) const {
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

// Subtraction
Vector4 Vector4::operator-(const Vector4& other) const {
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

// Scaling
Vector4 Vector4::operator*(const float scalar) const {
    return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

// Division
Vector4 Vector4::operator/(const float scalar) const {
    return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

// Compound assignment operators
Vector4& Vector4::operator+=(const Vector4& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

Vector4& Vector4::operator-=(const Vector4& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

Vector4& Vector4::operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Vector4& Vector4::operator/=(const float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

// Rotation around the X-axis
Vector4 Vector4::rotationX(const Vector4& vec, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return Vector4(
        vec.x,
        vec.y * c - vec.z * s,
        vec.y * s + vec.z * c,
        vec.w
    );
}

// Rotation around the Y-axis
Vector4 Vector4::rotationY(const Vector4& vec, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return Vector4(
        vec.x * c + vec.z * s,
        vec.y,
        -vec.x * s + vec.z * c,
        vec.w
    );
}

// Rotation around the Z-axis
Vector4 Vector4::rotationZ(const Vector4& vec, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return Vector4(
        vec.x * c - vec.y * s,
        vec.x * s + vec.y * c,
        vec.z,
        vec.w
    );
}

// Scaling
Vector4 Vector4::scaling(const Vector4& vec, float sx, float sy, float sz) {
    return Vector4(
        vec.x * sx,
        vec.y * sy,
        vec.z * sz,
        vec.w
    );
}

// Translation
Vector4 Vector4::translate(const Vector4& vec, float tx, float ty, float tz) {
    return Vector4(
        vec.x + tx,
        vec.y + ty,
        vec.z + tz,
        vec.w
    );
}

// Dot product
float Vector4::dot(const Vector4& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

// Cross product (only makes sense for 3D vectors, so we ignore w)
Vector4 Vector4::cross(const Vector4& other) const {
    return Vector4(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x,
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
