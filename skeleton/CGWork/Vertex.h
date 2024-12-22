#ifndef	VERTEX_H
#define	VERTEX_H
#include "Matrix4.h"
#include "Vector4.h"
#include <vector>
//#include "Polygon.h"
//
class PolygonGC;
//extern Vector3 getCalcNormal();


class Vertex {
private:
    Vector3 m_point;
    Vector3 m_dataNormal;    
    bool m_hasDataNormal;  
    Vector3 m_calcNormal;
    bool m_hasCalcNormal;
    std::vector<PolygonGC*> m_neigberPolygons;

    void setDataNormal(Vector3 normal);
    
public:
    
    // Constructor
    // Vertex(const Vertex& v);
    Vertex(Vector3 p);
    Vertex(Vector3 p, Vector3 n);
    
    void addNeigberPolygon(PolygonGC* poly);
    Vector3 getCalcNormal()const ;
    void setCalcNormal();
    // Print function
    void print();
    Vector3 loc() const;
    Vector3 getDataNormal() const;
    bool hasDataNormal() const;
    
    std::shared_ptr<Vertex> getTransformedVertex(const Matrix4& transformation)const;
    void transformVertex(const Matrix4& transformation);
    bool isInsideClipVolume();
    // Overload compound assignment operator for matrix multiplication
    Vertex& operator*=(const Matrix4& mat);
    // Overload multiplication operator to accept matrix operation
    friend Vertex operator*(const Matrix4& mat, const Vertex& vert);
    //One of the vertex must be out!and one must be in
    //static Vertex* intersectClipVolume(Vertex* v1, Vertex* v2) {
    //    Vector3 temp;
    //    //pos x
    //    temp = intersectPoint(v2->loc()- v1->loc(), v1->loc(), Vector3(1, 0, 0), Vector3(1, 0, 0));
    //    if (Vertex(temp).isInsideClipVolume())
    //    {
    //        return new Vertex(temp);
    //    }
    //    //neg x
    //    temp = intersectPoint(v2->loc() - v1->loc(), v1->loc(), Vector3(-1, 0, 0), Vector3(-1, 0, 0));
    //    if (Vertex(temp).isInsideClipVolume())
    //    {
    //        return new Vertex(temp);
    //    }
    //    //pos y
    //    temp = intersectPoint(v2->loc() - v1->loc(), v1->loc(), Vector3(0,1 , 0), Vector3(0, 1, 0));
    //    if (Vertex(temp).isInsideClipVolume())
    //    {
    //        return new Vertex(temp);
    //    }
    //    //neg y
    //    temp = intersectPoint(v2->loc() - v1->loc(), v1->loc(), Vector3(0, -1, 0), Vector3(0, -1, 0));
    //    if (Vertex(temp).isInsideClipVolume())
    //    {
    //        return new Vertex(temp);
    //    }
    //    //pos z
    //    temp = intersectPoint(v2->loc() - v1->loc(), v1->loc(), Vector3(0, 0, 1), Vector3(0, 0, 1));
    //    if (Vertex(temp).isInsideClipVolume())
    //    {
    //        return new Vertex(temp);
    //    }
    //    //neg z
    //    temp = intersectPoint(v2->loc() - v1->loc(), v1->loc(), Vector3(0, 0, -1), Vector3(0, 0, -1));
    //    if (Vertex(temp).isInsideClipVolume())
    //    {
    //        return new Vertex(temp);
    //    }
    //}
};


#endif // VERTEX_H
