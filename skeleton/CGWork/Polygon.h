#ifndef	POLYGON_H
#define	POLYGON_H
#include <vector>
#include "Vertex.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "iritprsr.h"

//might be useful
class BBox {
    Vector4 m_min_min, m_max_max;
};

//might be useful
class Line {
    Vertex m_a, m_b;
public:
    //create a line from a to b
    Line(const Vertex& a, const Vertex& b) : m_a(a), m_b(b) {};
};

class PolygonGC {
private:
    std::vector<Vertex*> m_vertices; // List of vertices
    Vector4 m_color;                // Color of the polygon
    Vector4 m_minBounds;            // Minimum bounds
    Vector4 m_maxBounds;            // Maximum bounds
    // Update min and max bounds
    void updateBounds(const Vertex& vert);

    void resetBounds();

public:
    // Constructor with a default color
    PolygonGC(int R = 0, int G = 0, int B = 0);

    // Set the color of the polygon
    void setColor(const Vector4& newColor);

    // Get the color of the polygon
    const Vector4& getColor();

    // Add a vertex
    void addVertexs(IPVertexStruct* vertex);

    // Get the number of vertices
    size_t vertexCount();

    // Print all vertices
    void printVertices();

    // Print bounds
    void printBounds();

    // Print polygon color
    void printColor();

    void applyTransformation(const Matrix4& transformation);

    BBox getBbox();
};
#endif