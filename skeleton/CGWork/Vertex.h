#ifndef	VERTEX_H
#define	VERTEX_H
#include "Matrix4.h"
#include "Vector4.h"

class Vertex {
private:
    Vector4 m_point;
    Vector4 m_normal;
    bool m_hasNormal;
public:

    // Constructor
    Vertex(Vector4 p) : m_point(p), m_normal(Vector4(0, 0, 0, 1)), m_hasNormal(false) {}
    // Constructor
    Vertex(Vector4 p, Vector4 n) : m_point(p), m_normal(n), m_hasNormal(true) {}

    // Print function
    void print() {
        std::cout << "Vertex Located at: " << m_point << ", with normal at: " << m_normal << std::endl;
    }

    Vector4 loc() const    // Get location
    {
        return m_point;
    }
    
    Vector4 normal() const {
        return m_normal;
    }
    bool hasNormal() const {
        return m_hasNormal;
    }
    void calculateNormal() const {
        //how?
    }
    bool isInsideClipVolume() {
        return m_point.x >= -m_point.w && m_point.x <= m_point.w &&
            m_point.y >= -m_point.w && m_point.y <= m_point.w &&
            m_point.z >= -m_point.w && m_point.z <= m_point.w;
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

static Vertex* intersectClipVolume(const Vertex* v1, const Vertex* v2) {
    // Calculate intersection point (simplified example)
    return new Vertex(Vector4::unitX());
}

#endif // VERTEX_H
