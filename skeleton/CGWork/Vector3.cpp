#include "Vector3.h"

// Constructor
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

// Addition
Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

// Subtraction
Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

// Scaling
Vector3 Vector3::operator*(const float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

// Division
Vector3 Vector3::operator/(const float scalar) const {
    return Vector3(x / scalar, y / scalar, z / scalar);
}

// Compound assignment operators
Vector3& Vector3::operator+=(const Vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3& Vector3::operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3& Vector3::operator/=(const float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

// Rotation around the X-axis
Vector3 Vector3::rotationX(const Vector3& vec, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return Vector3(
        vec.x,
        vec.y * c - vec.z * s,
        vec.y * s + vec.z * c
    );
}

// Rotation around the Y-axis
Vector3 Vector3::rotationY(const Vector3& vec, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return Vector3(
        vec.x * c + vec.z * s,
        vec.y,
        -vec.x * s + vec.z * c
    );
}

// Rotation around the Z-axis
Vector3 Vector3::rotationZ(const Vector3& vec, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return Vector3(
        vec.x * c - vec.y * s,
        vec.x * s + vec.y * c,
        vec.z
    );
}

// Scaling
Vector3 Vector3::scaling(const Vector3& vec, float sx, float sy, float sz) {
    return Vector3(
        vec.x * sx,
        vec.y * sy,
        vec.z * sz
    );
}

// Translation
Vector3 Vector3::translate(const Vector3& vec, float tx, float ty, float tz) {
    return Vector3(
        vec.x + tx,
        vec.y + ty,
        vec.z + tz
    );
}

// Dot product
float Vector3::dot(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Cross product
Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2) {
    return Vector3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

// Magnitude
float Vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Normalize
Vector3 Vector3::normalized() const {
    float len = length();
    if (len > 0) {
        return Vector3(x / len, y / len, z / len);
    }
    return Vector3();
}

// Static functions for common vectors
Vector3 Vector3::zero() {
    return Vector3(0, 0, 0);
}

Vector3 Vector3::one() {
    return Vector3(1, 1, 1);
}

Vector3 Vector3::unitX() {
    return Vector3(1, 0, 0);
}

Vector3 Vector3::unitY() {
    return Vector3(0, 1, 0);
}

Vector3 Vector3::unitZ() {
    return Vector3(0, 0, 1);
}

// Print
void Vector3::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

Vector3 operator-(const Vector3& vec) {
    return Vector3(-vec.x, -vec.y, -vec.z);
}
// Overload stream insertion operator
std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

// Overload stream extraction operator for formatted input
std::istream& operator>>(std::istream& is, Vector3& vec) {
    char comma;
    if (!(is >> vec.x >> comma >> vec.y >> comma >> vec.z)) {
        is.setstate(std::ios::failbit);
    }
    return is;
}

// Overload stream extraction operator for string input
std::istringstream& operator>>(std::istringstream& iss, Vector3& vec) {
    char comma;
    if (!(iss >> vec.x >> comma >> vec.y >> comma >> vec.z)) {
        iss.setstate(std::ios::failbit);
    }
    return iss;
}

float& Vector3::operator[](std::size_t index) {
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    throw std::out_of_range("Index must be 0, 1, or 2");
}

// Access operator for reading only
const float& Vector3::operator[](std::size_t index) const {
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    throw std::out_of_range("Index must be 0, 1, or 2");
}

bool Vector3::operator==(const Vector3& other) const {
    return x == other.x && y == other.y && z == other.z;
}

bool Vector3::intersectPointInClipVolume(Vector3 rayVector, Vector3 rayPoint, Vector3 planeNormal, Vector3 planePoint,Vector3& intersectPoint) {
    Vector3 diff = rayPoint - planePoint;
    double prod1 = Vector3::dot(diff, planeNormal);
    double prod2 = Vector3::dot(rayVector, planeNormal);
    if (prod2 == 0)
    {
        return false;
    }
    double prod3 = prod1 / prod2;
    intersectPoint= rayPoint - rayVector * prod3;
    if (intersectPoint.isInsideClipVolume())
    {
        return true;
    }
    return false;
}

bool Vector3::isInsideClipVolume()
{
    
    return x >= -1 && x <= 1 &&
           y >= -1 && y <= 1 &&
           z >= -1 && z <= 1;

}
