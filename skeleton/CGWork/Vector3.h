#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <sstream>
#include <cmath>

class Vector3 {
public:
    float x, y, z;

    // Constructor
    Vector3(float x = 0, float y = 0, float z = 0);

    // Addition
    Vector3 operator+(const Vector3& other) const;

    // Subtraction
    Vector3 operator-(const Vector3& other) const;

    // Scaling
    Vector3 operator*(const float scalar) const;

    // Division
    Vector3 operator/(const float scalar) const;

    // Compound assignment operators
    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator*=(const float scalar);
    Vector3& operator/=(const float scalar);

    // Rotation around the X-axis
    static Vector3 rotationX(const Vector3& vec, float angle);

    // Rotation around the Y-axis
    static Vector3 rotationY(const Vector3& vec, float angle);

    // Rotation around the Z-axis
    static Vector3 rotationZ(const Vector3& vec, float angle);

    // Scaling
    static Vector3 scaling(const Vector3& vec, float sx, float sy, float sz);

    // Translation
    static Vector3 translate(const Vector3& vec, float tx, float ty, float tz);

    // Dot product
    static float dot(const Vector3& v1, const Vector3& v2);

    // Cross product
    static Vector3 cross(const Vector3& v1, const Vector3& v2);

    // Magnitude
    float length() const;

    // Normalize
    Vector3 normalized() const;

    // Static functions for common vectors
    static Vector3 zero();
    static Vector3 one();
    static Vector3 unitX();
    static Vector3 unitY();
    static Vector3 unitZ();

    // Print
    void print() const;

    // Overload stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);

    // Overload stream extraction operator for formatted input
    friend std::istream& operator>>(std::istream& is, Vector3& vec);

    // Overload stream extraction operator for string input
    friend std::istringstream& operator>>(std::istringstream& iss, Vector3& vec);
};

#endif // VECTOR3_H
