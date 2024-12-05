#ifndef	POLYGON_H
#define	POLYGON_H
#include "Vertex.h"
#include "iritSkel.h"



class PolygonGC {
    std::vector<Vertex> m_vertices; // List of vertices
    Vector4 m_color;                // Color of the polygon
    Vector4 m_minBounds;            // Minimum bounds
    Vector4 m_maxBounds;            // Maximum bounds

    // Update min and max bounds
    void updateBounds();


public:
    // Constructor with a default color
    PolygonGC(int R , int G , int B);

    // Set the color of the polygon
    void setColor(const Vector4& newColor);

    // Get the color of the polygon
    const Vector4& getColor();

    // Add a vertex
    void addVertexs( IPVertexStruct* vertex);



    // Get the number of vertices
    size_t vertexCount();

    // Print all vertices
    void printVertices();

    // Print bounds
    void printBounds();

    // Print polygon color
    void printColor();
};
#endif