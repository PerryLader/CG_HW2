#ifndef	POLYGON_H
#define	POLYGON_H
#include <vector>
#include <set>
#include "Vertex.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "iritprsr.h"
#include "ColorGC.h"
#include <memory>

//might be useful
class BBox {
    Vector3 m_minBounds, m_maxBounds;
public:
    BBox() : m_minBounds(Vector3(FLT_MAX, FLT_MAX, FLT_MAX)), m_maxBounds(Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX)){};
    BBox(const Vector3& minBound, const Vector3& maxBound) : m_minBounds(minBound), m_maxBounds(maxBound) {};
    void updateBBox(const Vector3& vert);
    void updateBBox(const BBox& box);
    bool bboxCollide(const BBox& bbox) const;
    static bool bboxCollide(const BBox& bbox1, const BBox& bbox2);
    static BBox unitBBox() { return BBox(-Vector3::one(), Vector3::one()); }
    std::vector<Line> getLinesOfBbox(const ColorGC& bBoxColor) const;
    void toPrint() const;
};

//might be useful


class PolygonGC {
private:
    std::vector<std::shared_ptr< Vertex>> m_vertices; // List of vertices
    ColorGC m_color;                // Color of the polygon
    BBox m_bbox;
    Line m_calcNormalLine;
    Line m_dataNormalLine;
    bool m_hasDataNormal;
    void updateBounds(const Vertex& vert);
    void resetBounds();
    Vector3 calculateNormal() const;
public:
    // Constructor with a default color
    PolygonGC(ColorGC color);
    void setCalcAndDataNormalLines( Vector3 dataNormal);
    void setCalcNormalLines();
    Vector3 getCalcNormalNormolized();
    Vector3 getDataNormalNormolized();

    bool hasDataNormalLine() const;
    Line getCalcNormalLine(const ColorGC* overridingColor) const;
    Line getDataNormalLine(const ColorGC* overridingColor) const;
    std::vector<Line>* getVertNormLinesFromData(const ColorGC* overridingColor) const;
    std::vector<Line>* getVertNormLinesFromCalc(const ColorGC* overridingColor) const;
    void setColor(const ColorGC& newColor);
    const ColorGC& getColor() const;    
    void addVertex(std::shared_ptr<Vertex> vertex);    
    void clip();
    bool isBehindCamera() const;
    size_t vertexCount() const;
    void printVertices() const;
    void printBounds() const;
    void printColor() const;
    std::vector<Line> getPolyBboxLine(const ColorGC* overridingColor);
    PolygonGC* applyTransformation(const Matrix4& transformation) const;
    std::vector<Line>* getEdges(const ColorGC* overridingColor) const;
    BBox getBbox() const;
    ~PolygonGC()=default;
};
#endif