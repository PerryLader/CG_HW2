#ifndef VECTOR4_H
#define VECTOR4_H

#include <iostream>
#include <sstream>
#include <cmath>

class Vector4 {
public:
    float x, y, z, w;

    // Constructor
    Vector4(float x = 0, float y = 0, float z = 0, float w = 1);

    // Addition
    Vector4 operator+(const Vector4& other) const;

    // Subtraction
    Vector4 operator-(const Vector4& other) const;

    // Scaling
    Vector4 operator*(const float scalar) const;
    
    // Division
    Vector4 operator/(const float scalar) const;

    // Compound assignment operators
    Vector4& operator+=(const Vector4& other);
    Vector4& operator-=(const Vector4& other);
    Vector4& operator*=(const float scalar);
    Vector4& operator/=(const float scalar);

    // Rotation around the X-axis
    static Vector4 rotationX(const Vector4& vec, float angle);

    // Rotation around the Y-axis
    static Vector4 rotationY(const Vector4& vec, float angle);

    // Rotation around the Z-axis
    static Vector4 rotationZ(const Vector4& vec, float angle);

    // Scaling
    static Vector4 scaling(const Vector4& vec, float sx, float sy, float sz);

    // Translation
    static Vector4 translate(const Vector4& vec, float tx, float ty, float tz);

    // Dot product
    float dot(const Vector4& other) const;

    // Cross product (only makes sense for 3D vectors, so we ignore w)
    Vector4 cross(const Vector4& other) const;

    // Magnitude
    float length() const;

    // Normalize
    Vector4 normalized() const;

    // Static functions for common vectors
    static Vector4 zero();
    static Vector4 one();
    static Vector4 unitX();
    static Vector4 unitY();
    static Vector4 unitZ();
    static Vector4 unitW();

    // Print
    void print() const;

    // Overload stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Vector4& vec);

    // Overload stream extraction operator for formatted input
    friend std::istream& operator>>(std::istream& is, Vector4& vec);

    // Overload stream extraction operator for string input
    friend std::istringstream& operator>>(std::istringstream& iss, Vector4& vec);
};

#endif // VECTOR4_H
