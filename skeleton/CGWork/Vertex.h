#pragma once
#include <cmath>
#include <iostream>


class Vector4 {
public:
    float x, y, z, w;

    Vector4(float x = 0, float y = 0, float z = 0, float w = 0)
        : x(x), y(y), z(z), w(w) {}

    // Addition
    Vector4 operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    // Subtraction
    Vector4 operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    // Dot product
    float dot(const Vector4& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    // Magnitude
    float length() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    // Normalize
    Vector4 getNormalized() const {
        float mag = length();
        return mag == 0 ? Vector4() : Vector4(x / mag, y / mag, z / mag, w / mag);
    }

    // Print
    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")";
    }
};

class Vertex
{
public:
    Vector4 m_point;
    Vector4 m_normal;
    Vertex(Vector4 t) :m_point(t), m_normal(Vector4(0, 0, 0, 0)) {}
    void print() {
        std::cout << "Point: ";
        m_point.print();
        std::cout << ", Normal: ";
        m_normal.print();
        std::cout << std::endl;
    }
};


