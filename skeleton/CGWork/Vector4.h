#ifndef	VERCTOR4_H
#define	VERCTOR4_H
#include <iostream>
#include <string>

class Vector4 {
public:
    float x, y, z, w;

    Vector4(float x = 0, float y = 0, float z = 0, float w = 1);

    // Addition
    Vector4 operator+(const Vector4& other);

    // Subtraction
    Vector4 operator-(const Vector4& other);

    // Dot product
    float dot(const Vector4& other);

    // Magnitude
    float length();

    // Normalize
    Vector4 getNormalized();

    // Print
    void print();
};
#endif