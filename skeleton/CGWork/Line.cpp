#include "Line.h"





Line::Line(const Vertex& a, const Vertex& b, ColorGC color) : m_a(a.loc()), m_b(b.loc()),m_color(color) {}

// Calculate the direction vector of the line
Vector4 Line::direction() const {
    return (m_b - m_a).normalized();
}

// Calculate the length of the line
float Line::length() const {
    return (m_b - m_a).length();
}

// Check if two lines intersect, and return the intersection point if they do
bool Line::findIntersection(const Line& line1, const Line& line2, Vertex& interVertex) {
    // Line 1 direction vector
    //float d1x = line1.m_b.m_point.x - line1.m_a.m_point.x;
    //float d1y = line1.m_b.m_point.y - line1.m_a.m_point.y;
    //float d1z = line1.m_b.m_point.z - line1.m_a.m_point.z;

    //// Line 2 direction vector
    //float d2x = line2.m_b.m_point.x - line2.m_a.m_point.x;
    //float d2y = line2.m_b.m_point.y - line2.m_a.m_point.y;
    //float d2z = line2.m_b.m_point.z - line2.m_a.m_point.z;

    //// Difference between starting points
    //float px = line1.m_a.m_point.x - line2.m_a.m_point.x;
    //float py = line1.m_a.m_point.y - line2.m_a.m_point.y;
    //float pz = line1.m_a.m_point.z - line2.m_a.m_point.z;

    //// Dot products
    //float d1d1 = d1x * d1x + d1y * d1y + d1z * d1z;
    //float d2d2 = d2x * d2x + d2y * d2y + d2z * d2z;
    //float d1d2 = d1x * d2x + d1y * d2y + d1z * d2z;
    //float p1d1 = px * d1x + py * d1y + pz * d1z;
    //float p1d2 = px * d2x + py * d2y + pz * d2z;

    //// Determinant
    //float denominator = d1d1 * d2d2 - d1d2 * d1d2;

    //if (std::abs(denominator) < 1e-6) { // Lines are parallel or coincident
    //    return false;
    //}

    //// Solve for t and u
    //float t = (d2d2 * p1d1 - d1d2 * p1d2) / denominator;
    //float u = (d1d1 * p1d2 - d1d2 * p1d1) / denominator;

    //// Calculate intersection points
    //float intersectX1 = line1.m_a.m_point.x + t * d1x;
    //float intersectY1 = line1.m_a.m_point.y + t * d1y;
    //float intersectZ1 = line1.m_a.m_point.z + t * d1z;

    //float intersectX2 = line2.m_a.m_point.x + u * d2x;
    //float intersectY2 = line2.m_a.m_point.y + u * d2y;
    //float intersectZ2 = line2.m_a.m_point.z + u * d2z;

    //// Check if the points are within a tolerance (for numerical stability)
    //if (std::abs(intersectX1 - intersectX2) < 1e-6 &&
    //    std::abs(intersectY1 - intersectY2) < 1e-6 &&
    //    std::abs(intersectZ1 - intersectZ2) < 1e-6)
    //{

    //    interVertex.m_point.x = intersectX1;
    //    interVertex.m_point.y = intersectY1;
    //    interVertex.m_point.z = intersectZ1;
    //    interVertex.m_point.w = 1;

    //    return true;
    //}

    return false; // No intersection within segments
}

//void Line::DrawLineBresenham( pDC, int x1, int y1, int x2, int y2, COLORREF color)
//{
//
//}

void Line::draw(float* m_Buffer,int width,int hight)
{
    // Calculate differences
    int halfWidth = width / 2;
    int halfhight = hight / 2;
    int x1 = (m_a.x * halfWidth) + halfWidth;
    int x2 = (m_b.x * halfWidth) + halfWidth;
    int y1 = (m_a.y*halfhight)+halfhight;
    int y2 = (m_b.y * halfhight) + halfhight;


    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1; // Step for x
    int sy = (y1 < y2) ? 1 : -1; // Step for y
    int err = dx - dy;
    int color = m_color.getRGBA();

    while (true)
    {
        int xx = (y1 * width) + x1;
        // Draw the pixel at the current position
        m_Buffer[(y1 * width) + x1] = color;
        //pDC->SetPixelV(x1, y1, color);

        // Break when we reach the end point
        if (x1 == x2 && y1 == y2)
            break;

        // Calculate error and adjust positions
        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

// Print the line
void Line::print() {
    std::cout << "Line[";
    std::cout << "(" << m_a.x << ", " << m_a.y << ", " << m_a.z << ", " << m_a.w << ")" <<
        " -> (" << m_b.x << ", " << m_b.y << ", " << m_b.z << ", " << m_b.w << ")" << "]";

}