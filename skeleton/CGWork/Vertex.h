#ifndef	VERTEX_H
#define	VERTEX_H
#include "Matrix4.h"
#include "Vector4.h"
#include <vector>
class Vertex {
private:
    Vector3 m_point;
    Vector3 m_normal;
    bool m_hasNormal;   
    static Vector3 intersectPoint(Vector3 rayVector, Vector3 rayPoint, Vector3 planeNormal, Vector3 planePoint) {
        Vector3 diff = rayPoint - planePoint;
        double prod1 = Vector3::dot(diff, planeNormal);
        double prod2 = Vector3::dot(rayVector, planeNormal);
        double prod3 = prod1 / prod2;
        return rayPoint - rayVector * prod3;
    }
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
   
    //One of the vertex must be out!and one must be in
    static Vertex* intersectClipVolume(Vertex* v1, Vertex* v2) {
        Vector3 temp;
        //pos x
        temp = intersectPoint(v2->loc()- v1->loc(), v1->loc(), Vector3(1, 0, 0), Vector3(1, 0, 0));
        if (Vertex(temp).isInsideClipVolume())
        {
            return new Vertex(temp);
        }
        //neg x
        temp = intersectPoint(v2->loc() - v1->loc(), v1->loc(), Vector3(-1, 0, 0), Vector3(-1, 0, 0));
        if (Vertex(temp).isInsideClipVolume())
        {
            return new Vertex(temp);
        }
        //pos y
        temp = intersectPoint(v2->loc() - v1->loc(), v1->loc(), Vector3(0,1 , 0), Vector3(0, 1, 0));
        if (Vertex(temp).isInsideClipVolume())
        {
            return new Vertex(temp);
        }
        //neg y
        temp = intersectPoint(v2->loc() - v1->loc(), v1->loc(), Vector3(0, -1, 0), Vector3(0, -1, 0));
        if (Vertex(temp).isInsideClipVolume())
        {
            return new Vertex(temp);
        }
        //pos z
        temp = intersectPoint(v2->loc() - v1->loc(), v1->loc(), Vector3(0, 0, 1), Vector3(0, 0, 1));
        if (Vertex(temp).isInsideClipVolume())
        {
            return new Vertex(temp);
        }
        //neg z
        temp = intersectPoint(v2->loc() - v1->loc(), v1->loc(), Vector3(0, 0, -1), Vector3(0, 0, -1));
        if (Vertex(temp).isInsideClipVolume())
        {
            return new Vertex(temp);
        }

        //pos y
        //neg y
        //pos z
        
        
        //neg z


        //double boxSize = 2;
        //double epsilon = 0.0;
        //double halfSize = boxSize / 2.0;
        //Vector3 boxMin(-halfSize, -halfSize, -halfSize);
        //Vector3 boxMax(halfSize, halfSize, halfSize);
        //bool v1In = v1->isInsideClipVolume();
        //bool v2In = v2->isInsideClipVolume();

        //if ((!v1In && !v2In) || (v1In && v2In))
        //{
        //    throw;
        //}

        //for (int axis = 0; axis < 3; ++axis) {
        //    // Check for intersection with planes on the current axis
        //    double tMin, tMax;

        //    if (std::abs(v2->loc()[axis]) == 0) {
        //       epsilon += 0.01;

        //    }// Avoid division by zero
        //    tMin = (boxMin[axis] - v1->loc()[axis]) / (v2->loc()[axis] + epsilon);
        //    tMax = (boxMax[axis] - v1->loc()[axis]) / (v2->loc()[axis] + epsilon);

        //    if (tMin > tMax) std::swap(tMin, tMax);

        //    // Check if the intersection points are within the bounds of the box for other axes
        //    for (double t : {tMin, tMax}) {
        //        Vector3 intersection = v1->loc() + (v2->loc() * t);
        //        epsilon *= 5;
        //        if (isWithin(intersection.x, boxMin.x - epsilon, boxMax.x + epsilon) &&
        //            isWithin(intersection.y, boxMin.y - epsilon, boxMax.y + epsilon) &&
        //            isWithin(intersection.z, boxMin.z - epsilon, boxMax.z + epsilon) /* &&
        //           isPointBetween(v1->loc(), v2->loc(), intersection)*/) {
        //            return (new Vertex(intersection));
        //        }
        //    }
        //    epsilon - 0;


        //}
        //throw;




    }

};


#endif // VERTEX_H
