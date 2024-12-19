#ifndef	VERTEX_H
#define	VERTEX_H
#include "Matrix4.h"
#include "Vector4.h"

class Vertex {
private:
    Vector3 m_point;
    Vector3 m_normal;
    bool m_hasNormal;
public:

    // Constructor
    Vertex(Vector3 p) : m_point(p), m_normal(Vector3(0, 0, 0)), m_hasNormal(false) {}
    // Constructor
    Vertex(Vector3 p, Vector3 n) : m_point(p), m_normal(n), m_hasNormal(true) {}

    // Print function
    void print() {
        std::cout << "Vertex Located at: " << m_point << ", with normal at: " << m_normal << std::endl;
    }

    Vector3 loc() const    // Get location
    {
        return m_point;
    }
    
    Vector3 normal() const {
        return m_normal;
    }
    bool hasNormal() const {
        return m_hasNormal;
    }
    void calculateNormal() const {
        //how?
    }
    bool isInsideClipVolume() {
        return m_point.x >= -1 && m_point.x <= 1 &&
            m_point.y >= -1 && m_point.y <= 1 &&
            m_point.z >= -1 && m_point.z <= 1;
    }

    // Overload compound assignment operator for matrix multiplication
    Vertex& operator*=(const Matrix4& mat) {
        m_point = (mat * Vector4::extendOne(m_point)).toVector3();
        m_normal = (mat * Vector4::extendOne(m_normal)).toVector3();
        return *this;
    }
    // Overload multiplication operator to accept matrix operation
    friend Vertex operator*(const Matrix4& mat, const Vertex& vert) {
        Vertex res = Vertex((mat * Vector4::extendOne(vert.m_point)).toVector3());
        res.m_normal = (mat * Vector4::extendOne(res.m_normal)).toVector3();
        return res;
    }
};

static Vertex* intersectClipVolume(const Vertex* v1, const Vertex* v2) {
    //todo!!!
    // Calculate intersection point (simplified example)
    return new Vertex(Vector3::unitX());
}

#endif // VERTEX_H
