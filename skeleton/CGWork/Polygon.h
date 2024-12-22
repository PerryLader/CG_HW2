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
#include <memory>
//might be useful
class BBox {
    Vector3 m_minBounds, m_maxBounds;
public:
    BBox() : m_minBounds(), m_maxBounds(){};
    BBox(const Vector3& minBound, const Vector3& maxBound) : m_minBounds(minBound), m_maxBounds(maxBound) {};
    void updateBBox(const Vector3& vert);
    void updateBBox(const BBox& box);
    bool bboxCollide(const BBox& bbox) const;
    static bool bboxCollide(const BBox& bbox1, const BBox& bbox2);
    std::vector<Line> getLinesOfBbox(const ColorGC& bBoxColor);
    void toPrint() const;
};

//might be useful


class PolygonGC {
private:
    std::vector<std::shared_ptr< Vertex>> m_vertices; // List of vertices
    ColorGC m_color;                // Color of the polygon
    BBox m_bbox;
    Vector3 m_calcNormal;
    Vector3 m_dataNormal;
    bool m_hasDataNormal;
    void updateBounds(const Vertex& vert);
    void resetBounds();
    Vector3 calculateNormal() const;
public:
    // Constructor with a default color
    PolygonGC(ColorGC color);
    PolygonGC(const Vector3& normal, ColorGC color);
    
    bool hasDataNormal() const;
    Vector3 getCalcNormal() const;
    Vector3 getDataNormal() const;
    Line getNormalLineFromData(ColorGC normalColor) const;
    Line calcNormalLine(ColorGC normalColor) const;
   
    void setColor(const ColorGC& newColor);
    const ColorGC& getColor() const;
    
    void addVertexs(IPVertexStruct* vertex);     // Add many vertex with geershon struct unsupported not recommended
    void addVertex(std::shared_ptr<Vertex> vertex);   // Adds vertex
    
    void clip();
    bool isBehindCamera() const;
    std::vector<std::shared_ptr<Vertex>> getVertexVector();
    size_t vertexCount() const;
    void printVertices() const;
    void printBounds() const;
    void printColor() const;
    std::vector<Line> getPolyBboxLine(const ColorGC& bBoxColor);

    PolygonGC* applyForceTransformation(const Matrix4& transformation) const;

    PolygonGC* applySoftTransformation(const Matrix4& transformation) const;
    std::vector<Line>* getEdges() const;
    BBox getBbox() const;
    ~PolygonGC()=default;
};
#endif