#ifndef	POLYGON_H
#define	POLYGON_H
#include <vector>
#include <set>
#include "Vertex.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "iritprsr.h"
#include "Line.h"
#include "ColorGC.h"
//might be useful
class BBox {
    Vector3 m_minBounds, m_maxBounds;
public:
    BBox() : m_minBounds(), m_maxBounds(){};
    BBox(const Vector3& minBound, const Vector3& maxBound) : m_minBounds(minBound), m_maxBounds(maxBound) {};
    void updateBBox(const Vector3& vert);
    bool bboxCollide(const BBox& bbox) const;
    static bool bboxCollide(const BBox& bbox1, const BBox& bbox2);
    void toPrint() const;
};

//might be useful


class PolygonGC {
private:
    std::vector<Vertex*> m_vertices; // List of vertices
    ColorGC m_color;                // Color of the polygon
    BBox m_bbox;
    Vector3 m_nomal;
    // Update min and max bounds
    bool m_hasNormal;
    void updateBounds(const Vertex& vert);
    void resetBounds();
public:
    // Constructor with a default color
    PolygonGC(ColorGC color);
    PolygonGC(const Vector3& normal, ColorGC color);
    
    bool hasNormal() const;
    Vector3 getNormal() const;
    void calculateNormal();
   
    void setColor(const ColorGC& newColor);
    const ColorGC& getColor() const;
    
    void addVertexs(IPVertexStruct* vertex);     // Add many vertex with geershon struct unsupported not recommended
    void PolygonGC::addVertex(Vertex* vertex);   // Adds vertex
    

    void clip();
    bool isBehindCamera() const;

    size_t vertexCount() const;
    void printVertices() const;
    void printBounds() const;
    void printColor() const;

    PolygonGC* applyTransformation(const Matrix4& transformation) const;
    std::vector<Line>* getEdges() const;
    BBox getBbox() const;
    ~PolygonGC();
};
#endif