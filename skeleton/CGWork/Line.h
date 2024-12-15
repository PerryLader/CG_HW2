#pragma once
#include "Vertex.h"
#include "Vector4.h"


class Line {
public:
    Vertex m_a, m_b;


    // Constructor to create a line from vertex a to vertex b
    Line(const Vertex& a, const Vertex& b);

    // Calculate the direction vector of the line
    Vertex direction()const;

    // Calculate the length of the line
    float length()const;

    // Check if two lines intersect, and return the intersection point if they do
    static bool findIntersection(const Line& line1, const Line& line2, Vertex& interVertex);

    // Print the line
    void print();
};
