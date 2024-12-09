#include "Line.h"





Line::Line(const Vertex& a, const Vertex& b) : m_a(a), m_b(b) {}

// Calculate the direction vector of the line
Vertex Line::direction() const {
    return Vertex(Vector4(m_b.m_point.x - m_a.m_point.x, m_b.m_point.y - m_a.m_point.y, m_b.m_point.z - m_a.m_point.z));
}

// Calculate the length of the line
float Line::length() const {
    return std::sqrt(std::pow(m_b.m_point.x - m_a.m_point.x, 2) + std::pow(m_b.m_point.y - m_a.m_point.y, 2) + std::pow(m_b.m_point.z - m_a.m_point.z, 2));
}

// Check if two lines intersect, and return the intersection point if they do
bool Line::findIntersection(const Line& line1, const Line& line2, Vertex& interVertex) {
    // Line 1 direction vector
    float d1x = line1.m_b.m_point.x - line1.m_a.m_point.x;
    float d1y = line1.m_b.m_point.y - line1.m_a.m_point.y;
    float d1z = line1.m_b.m_point.z - line1.m_a.m_point.z;

    // Line 2 direction vector
    float d2x = line2.m_b.m_point.x - line2.m_a.m_point.x;
    float d2y = line2.m_b.m_point.y - line2.m_a.m_point.y;
    float d2z = line2.m_b.m_point.z - line2.m_a.m_point.z;

    // Difference between starting points
    float px = line1.m_a.m_point.x - line2.m_a.m_point.x;
    float py = line1.m_a.m_point.y - line2.m_a.m_point.y;
    float pz = line1.m_a.m_point.z - line2.m_a.m_point.z;

    // Dot products
    float d1d1 = d1x * d1x + d1y * d1y + d1z * d1z;
    float d2d2 = d2x * d2x + d2y * d2y + d2z * d2z;
    float d1d2 = d1x * d2x + d1y * d2y + d1z * d2z;
    float p1d1 = px * d1x + py * d1y + pz * d1z;
    float p1d2 = px * d2x + py * d2y + pz * d2z;

    // Determinant
    float denominator = d1d1 * d2d2 - d1d2 * d1d2;

    if (std::abs(denominator) < 1e-6) { // Lines are parallel or coincident
        return false;
    }

    // Solve for t and u
    float t = (d2d2 * p1d1 - d1d2 * p1d2) / denominator;
    float u = (d1d1 * p1d2 - d1d2 * p1d1) / denominator;

    // Calculate intersection points
    float intersectX1 = line1.m_a.m_point.x + t * d1x;
    float intersectY1 = line1.m_a.m_point.y + t * d1y;
    float intersectZ1 = line1.m_a.m_point.z + t * d1z;

    float intersectX2 = line2.m_a.m_point.x + u * d2x;
    float intersectY2 = line2.m_a.m_point.y + u * d2y;
    float intersectZ2 = line2.m_a.m_point.z + u * d2z;

    // Check if the points are within a tolerance (for numerical stability)
    if (std::abs(intersectX1 - intersectX2) < 1e-6 &&
        std::abs(intersectY1 - intersectY2) < 1e-6 &&
        std::abs(intersectZ1 - intersectZ2) < 1e-6)
    {

        interVertex.m_point.x = intersectX1;
        interVertex.m_point.y = intersectY1;
        interVertex.m_point.z = intersectZ1;
        interVertex.m_point.w = 1;

        return true;
    }

    return false; // No intersection within segments
}

// Print the line
void Line::print() {
    std::cout << "Line[";
    std::cout << "(" << m_a.m_point.x << ", " << m_a.m_point.y << ", " << m_a.m_point.z << ", " << m_a.m_point.w << ")" <<
        " -> (" << m_b.m_point.x << ", " << m_b.m_point.y << ", " << m_b.m_point.z << ", " << m_b.m_point.w << ")" << "]";

}