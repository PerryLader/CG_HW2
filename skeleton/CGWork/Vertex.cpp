<<<<<<< HEAD
#include "Vertex.h"
#include "Polygon.h"
//
//class PolygonGC;
//extern Vector3 getCalcNormal();



   

void Vertex::setDataNormal(Vector3 normal) {
    m_dataNormal = normal;
    m_hasDataNormal = true;
}

//Vertex::Vertex(const Vertex &v)
//{
//    m_calcNormal=v.
//}

// Constructor
Vertex::Vertex(Vector3 p) : m_point(p), m_dataNormal(Vector3(0, 0, 0)), m_hasDataNormal(false), m_hasCalcNormal(false) {}
// Constructor
Vertex::Vertex(Vector3 p, Vector3 n) : m_point(p), m_dataNormal(n), m_hasDataNormal(true), m_hasCalcNormal(false) {}



void Vertex::addNeigberPolygon(PolygonGC* poly) { m_neigberPolygons.push_back(poly); }

Vector3 Vertex::getCalcNormal()const
{
    if (!m_hasCalcNormal)
    {
        throw;
    }
    return m_calcNormal;    
}
void Vertex::setCalcNormal()
{
    
    Vector3 avrageNormal(0, 0, 0);
    for (PolygonGC* t : m_neigberPolygons)
    {
        avrageNormal = avrageNormal + t->getCalcNormal();
    }
    this->m_calcNormal= avrageNormal * (1.0 / m_neigberPolygons.size());
    m_hasCalcNormal = true;
}
// Print function
void Vertex::print() {
    std::cout << "Vertex Located at: " << m_point << std::endl;
}
Vector3 Vertex::loc() const    // Get location
{
    return m_point;
}
Vector3 Vertex::getDataNormal() const {
    return m_dataNormal;
}
bool Vertex::hasDataNormal() const {
    return m_hasDataNormal;
}

std::shared_ptr<Vertex> Vertex::getTransformedVertex(const Matrix4& transformation)const
{
    std::shared_ptr<Vertex> temp(  new Vertex((transformation * Vector4::extendOne(this->m_point)).toVector3()));
    if (m_hasCalcNormal)
    {
        temp->m_hasCalcNormal = true;
        temp->m_calcNormal=((transformation * Vector4::extendOne(temp->m_calcNormal)).toVector3());
    }
    if (m_hasDataNormal)
    {
        temp->m_hasDataNormal = true;
        temp->setDataNormal((transformation * Vector4::extendOne(this->m_dataNormal)).toVector3());

    }
    return temp;
}
void Vertex::transformVertex(const Matrix4& transformation)
{
    m_point = ((transformation * Vector4::extendOne(this->m_point)).toVector3());
    if (m_hasCalcNormal)
    {
        m_calcNormal = ((transformation * Vector4::extendOne(this->m_calcNormal)).toVector3());
    }
    if (m_hasDataNormal)
    {
        m_dataNormal = ((transformation * Vector4::extendOne(this->m_dataNormal)).toVector3());

    }
}
bool Vertex::isInsideClipVolume() {
    return m_point.x >= -1 && m_point.x <= 1 &&
        m_point.y >= -1 && m_point.y <= 1 &&
        m_point.z >= -1 && m_point.z <= 1;
}
// Overload compound assignment operator for matrix multiplication
Vertex& Vertex::operator*=(const Matrix4& mat) {
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
Vertex operator*(const Matrix4& mat, const Vertex& vert)
{
    Vertex res = Vertex((mat * Vector4::extendOne(vert.m_point)).toVector3());
    if (vert.hasDataNormal())
    {
        res.m_dataNormal = (mat * Vector4::extendOne(vert.m_dataNormal)).toVector3();
    }
    if (vert.m_hasCalcNormal)
    {
        res.m_calcNormal=((mat * Vector4::extendOne(vert.m_calcNormal)).toVector3());
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
=======
#include "Vertex.h"
#include "Polygon.h"
//
//class PolygonGC;
//extern Vector3 getCalcNormal();



   

void Vertex::setDataNormal(Vector3 normal) {
    m_dataNormal = normal;
    m_hasDataNormal = true;
}

//Vertex::Vertex(const Vertex &v)
//{
//    m_calcNormal=v.
//}

// Constructor
Vertex::Vertex(Vector3 p) : m_point(p), m_dataNormal(Vector3(0, 0, 0)), m_hasDataNormal(false), m_hasCalcNormal(false) {}
// Constructor
Vertex::Vertex(Vector3 p, Vector3 n) : m_point(p), m_dataNormal(n), m_hasDataNormal(true), m_hasCalcNormal(false) {}



void Vertex::addNeigberPolygon(PolygonGC* poly) { m_neigberPolygons.push_back(poly); }

Vector3 Vertex::getCalcNormal()const
{
    if (!m_hasCalcNormal)
    {
        throw;
    }
    return m_calcNormal;    
}
void Vertex::setCalcNormal()
{
    
    Vector3 avrageNormal(0, 0, 0);
    for (PolygonGC* t : m_neigberPolygons)
    {
        avrageNormal = avrageNormal + t->getCalcNormal();
    }
    this->m_calcNormal= avrageNormal * (1.0 / m_neigberPolygons.size());
    m_hasCalcNormal = true;
}
// Print function
void Vertex::print() {
    std::cout << "Vertex Located at: " << m_point << std::endl;
}
Vector3 Vertex::loc() const    // Get location
{
    return m_point;
}
Vector3 Vertex::getDataNormal() const {
    if (!m_hasDataNormal)
    {
        throw;
    }
    return m_dataNormal;
}
bool Vertex::hasDataNormal() const {
    return m_hasDataNormal;
}

std::shared_ptr<Vertex> Vertex::getTransformedVertex(const Matrix4& transformation)const
{
    std::shared_ptr<Vertex> temp(  new Vertex((transformation * Vector4::extendOne(this->m_point)).toVector3()));
    if (m_hasCalcNormal)
    {
        temp->m_hasCalcNormal = true;
        temp->m_calcNormal=((transformation * Vector4::extendOne(temp->m_calcNormal)).toVector3());
    }
    if (m_hasDataNormal)
    {
        temp->m_hasDataNormal = true;
        temp->setDataNormal((transformation * Vector4::extendOne(this->m_dataNormal)).toVector3());

    }
    return temp;
}
void Vertex::transformVertex(const Matrix4& transformation)
{
    m_point = ((transformation * Vector4::extendOne(this->m_point)).toVector3());
    if (m_hasCalcNormal)
    {
        m_calcNormal = ((transformation * Vector4::extendOne(this->m_calcNormal)).toVector3());
    }
    if (m_hasDataNormal)
    {
        m_dataNormal = ((transformation * Vector4::extendOne(this->m_dataNormal)).toVector3());

    }
}
bool Vertex::isInsideClipVolume() {
    return m_point.x >= -1 && m_point.x <= 1 &&
        m_point.y >= -1 && m_point.y <= 1 &&
        m_point.z >= -1 && m_point.z <= 1;
}
// Overload compound assignment operator for matrix multiplication
Vertex& Vertex::operator*=(const Matrix4& mat) {
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
Vertex operator*(const Matrix4& mat, const Vertex& vert)
{
    Vertex res = Vertex((mat * Vector4::extendOne(vert.m_point)).toVector3());
    if (vert.hasDataNormal())
    {
        res.m_dataNormal = (mat * Vector4::extendOne(vert.m_dataNormal)).toVector3();
    }
    if (vert.m_hasCalcNormal)
    {
        res.m_calcNormal=((mat * Vector4::extendOne(vert.m_calcNormal)).toVector3());
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
>>>>>>> ed1b721 (calc vert Normal with new renderMode)
