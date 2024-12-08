#ifndef	VERTEX_H
#define	VERTEX_H
#include "Matrix4.h"
#include "Vector4.h"

class Vertex {
public:
    Vector4 m_point;
    Vector4 m_normal;

    // Constructor
    Vertex(Vector4 p) : m_point(p), m_normal(Vector4(0, 0, 0, 0)) {}
    // Constructor
    Vertex(Vector4 p, Vector4 n) : m_point(p), m_normal(n) {}

    // Print function
    void print() {
        m_point.print();
        // std::cout << ", Normal: ";
        // m_normal.print();
    }

    // Get location
    Vector4 location() const {
        return m_point;
    }

    // Overload compound assignment operator for matrix multiplication
    Vertex& operator*=(const Matrix4& mat) {
        m_point = mat * m_point;
        m_normal = mat * m_normal;
        return *this;
    }
    // Overload multiplication operator to accept matrix operation
    friend Vertex operator*(const Matrix4& mat, const Vertex& vert) {
        Vertex res = Vertex(mat * vert.m_point);
        res.m_normal = mat * res.m_normal;
        return res;
    }
};

#endif // VERTEX_H
