#ifndef	VERTEX_H
#define	VERTEX_H
#include "Matrix4.h"
#include "Vector4.h"

class Vertex {
public:
    Vector4 m_point;
    Vector4 m_normal;

    // Constructor
    Vertex(Vector4 t) : m_point(t), m_normal(Vector4(0, 0, 0, 0)) {}

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

    // Overload multiplication operator to accept matrix operation
    Vertex operator*(const Matrix4& mat) const {
        Vertex res = Vertex(mat * m_point);
        //.m_normal *= mat;
        return res;
    }

    // Overload compound assignment operator for matrix multiplication
    Vertex& operator*=(const Matrix4& mat) {
        m_point = mat * m_point;
        m_normal = mat * m_normal;
        return *this;
    }
};

#endif // VERTEX_H
