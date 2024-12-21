#ifndef	VERTEX_H
#define	VERTEX_H
#include "Matrix4.h"
#include "Vector4.h"
#include <vector>


class Vertex {
private:
    Vector3 m_point;
    Vector3 m_dataNormal;    
    bool m_hasDataNormal;  
    Vector3 m_calcNormal;
    bool m_hasCalcNormal;
    void setCalcNormal(Vector3 normal) {
        m_calcNormal = normal;
        m_hasCalcNormal = true;
    }
    void setDataNormal(Vector3 normal) {
        m_dataNormal = normal;
        m_hasDataNormal = true;
    }
public:

    // Constructor
    Vertex(Vector3 p) : m_point(p), m_dataNormal(Vector3(0, 0, 0)), m_hasDataNormal(false), m_hasCalcNormal(false) {}
    // Constructor
    Vertex(Vector3 p, Vector3 n) : m_point(p), m_dataNormal(n), m_hasDataNormal(true) ,m_hasCalcNormal(false){}

    // Print function
    void print() {
        std::cout << "Vertex Located at: " << m_point << std::endl;
    }
    Vector3 loc() const    // Get location
    {
        return m_point;
    }
    Vector3 getDataNormal() const {
        return m_dataNormal;
    }
    bool hasDataNormal() const {
        return m_hasDataNormal;
    }
    void calculateNormal() const {
        //how?
    }
    Vertex* getTransformedVertex(const Matrix4& transformation)const
    {
        Vertex* temp = new Vertex((transformation * Vector4::extendOne(this->m_point)).toVector3()    );
        if (m_hasCalcNormal)
        {
            temp->setCalcNormal(m_calcNormal);
        }
        if (m_hasDataNormal)
        {
            temp->setDataNormal(m_calcNormal);
           
        }
        return temp;
    }
    bool isInsideClipVolume() {
        return m_point.x >= -1 && m_point.x <= 1 &&
            m_point.y >= -1 && m_point.y <= 1 &&
            m_point.z >= -1 && m_point.z <= 1;
    }
    // Overload compound assignment operator for matrix multiplication
    Vertex& operator*=(const Matrix4& mat) {
        m_point = (mat * Vector4::extendOne(m_point)).toVector3();
        if (m_hasDataNormal)
        {
            m_dataNormal = (mat * Vector4::extendOne(m_dataNormal)).toVector3();
        }
        if (m_hasCalcNormal)
        {
            m_calcNormal = (mat * Vector4::extendOne(m_calcNormal)).toVector3();//TODO 
        }

        return *this;
    }
    // Overload multiplication operator to accept matrix operation
    friend Vertex operator*(const Matrix4& mat, const Vertex& vert) 
    {
        Vertex res = Vertex((mat * Vector4::extendOne(vert.m_point)).toVector3());
        if(vert.hasDataNormal())
        {
            res.m_dataNormal = (mat * Vector4::extendOne(vert.m_dataNormal)).toVector3();
        }
        if (vert.m_hasCalcNormal)
        {
            res.setCalcNormal((mat * Vector4::extendOne(vert.m_calcNormal)).toVector3());
        }
        return res;
    }
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
