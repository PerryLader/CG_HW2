#ifndef	POLYGON_H
#define	POLYGON_H
#include <vector>
#include <set>
#include "Vertex.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "iritprsr.h"
#include "Line.h"

//might be useful
class BBox {
    Vector4 m_minBounds, m_maxBounds;
public:
    BBox() : m_minBounds(), m_maxBounds(){};
    BBox(const Vector4& minBound, const Vector4& maxBound) : m_minBounds(minBound), m_maxBounds(maxBound) {};
    void updateBBox(const Vector4& vert);
    bool bboxCollide(const BBox& bbox) const;
    static bool bboxCollide(const BBox& bbox1, const BBox& bbox2);
    void toPrint() const;
};

//might be useful


class PolygonGC {
private:
    std::vector<Vertex*> m_vertices; // List of vertices
    Vector4 m_color;                // Color of the polygon
    BBox m_bbox;
    // Update min and max bounds
    
    void updateBounds(const Vertex& vert);
    void resetBounds();

public:

    Vector4 getNormal();
    // Constructor with a default color
    PolygonGC(int R = 0, int G = 0, int B = 0);
    // Set the color of the polygon
    void setColor(const Vector4& newColor);
    // Get the color of the polygon
    const Vector4& getColor();
    // Add many vertex
    void addVertexs(IPVertexStruct* vertex);
    // Add a vertex
    void PolygonGC::addVertex(Vertex* vertex);
    // Get the number of vertices
    size_t vertexCount();
    // Print all vertices
    void printVertices();
    // Print bounds
    void printBounds();
    // Print polygon color
    void printColor();

    void clip();
    bool isBehindCamera();
    PolygonGC* applyTransformation(const Matrix4& transformation) const;
    BBox getBbox();
    ~PolygonGC();
};
#endif