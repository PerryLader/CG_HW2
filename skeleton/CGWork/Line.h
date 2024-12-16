#pragma once
#include "Vertex.h"
#include "Vector4.h"
#include "ColorGC.h"

class Line {
public:
    Vector4 m_a, m_b;
    ColorGC m_color;

    // Constructor to create a line from vertex a to vertex b
    Line(const Vertex& a, const Vertex& b, ColorGC color);

    // Calculate the direction vector of the line
    Vector4 direction()const;

    // Calculate the length of the line
    float length()const;

    // Check if two lines intersect, and return the intersection point if they do
    static bool findIntersection(const Line& line1, const Line& line2, Vertex& interVertex);

    void draw(float* m_Buffer, int width);
    // Print the line
    void print();
//private:
//    static void DrawLineBresenham(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
};
