#ifndef	VERTEX_H
#define	VERTEX_H
#include <cmath>
#include <vector>
#include <limits>
#include <cfloat>
#include "Vector4.h"
#include <algorithm>



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

#endif
