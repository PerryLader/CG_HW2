#include "Vector4.h"



Vector4::Vector4(float x , float y, float z, float w )
    : x(x), y(y), z(z), w(w) {
}

// Addition
Vector4 Vector4::operator+(const Vector4& other) {
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

// Subtraction
Vector4 Vector4::operator-(const Vector4& other) {
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

// Dot product
float Vector4::dot(const Vector4& other) {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

// Magnitude
float Vector4::length() {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

// Normalize
Vector4 Vector4::getNormalized() {
    float mag = length();
    return mag == 0 ? Vector4() : Vector4(x / mag, y / mag, z / mag, w / mag);
}

// Print
void Vector4::print() {
    std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")";
}
