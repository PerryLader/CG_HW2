#include "Polygon.h"







// Update min and max bounds
void PolygonGC::updateBounds() {
    if (m_vertices.empty()) {
        m_minBounds = Vector4();
        m_maxBounds = Vector4();
        return;
    }

    m_minBounds = Vector4(FLT_MAX, FLT_MAX, FLT_MAX, 1);
    m_maxBounds = Vector4(-FLT_MAX, -FLT_MAX, -FLT_MAX, 1);

    for (const auto& vertex : m_vertices) {
        const auto& pos = vertex.m_point; // Assuming Vertex has a `position` member
        m_minBounds.x = std::min(m_minBounds.x, pos.x);
        m_minBounds.y = std::min(m_minBounds.y, pos.y);
        m_minBounds.z = std::min(m_minBounds.z, pos.z);
        //m_minBounds.w = min(m_minBounds.w, pos.w);

        m_maxBounds.x = std::max(m_maxBounds.x, pos.x);
        m_maxBounds.y = std::max(m_maxBounds.y, pos.y);
        m_maxBounds.z = std::max(m_maxBounds.z, pos.z);
        // m_maxBounds.w = max(m_maxBounds.w, pos.w);
    }
}


// Constructor with a default color
PolygonGC::PolygonGC(int R = 0, int G = 0, int B = 0) : m_color(R, G, B, 0) {
    updateBounds();
}

// Set the color of the polygon
void PolygonGC::setColor(const Vector4& newColor) {
    if (newColor.x < 0 || newColor.x>255 ||
        newColor.y < 0 || newColor.y>255 ||
        newColor.z < 0 || newColor.z>255)
        throw;
    m_color = newColor;
}

// Get the color of the polygon
const Vector4& PolygonGC::getColor()  {
    return m_color;
}

// Add a vertex
void PolygonGC::addVertexs( IPVertexStruct* vertex) {
    while (vertex)
    {
        Vector4 temp = Vector4(vertex->Coord[0],
            vertex->Coord[1],
            vertex->Coord[2], 1);
        m_vertices.push_back(Vertex(temp));
        vertex = vertex->Pnext;
    }
    
    updateBounds();
}



// Get the number of vertices
size_t PolygonGC::vertexCount()  {
    return m_vertices.size();
}


// Print all vertices
void PolygonGC::printVertices() {
    std::cout << "Polygon vertices:\n";
    for (size_t i = 0; i < m_vertices.size(); ++i) {
        std::cout << "  Vertex " << i + 1 << ": ";
        m_vertices[i].print(); // Assuming Vertex has a `print` method
        std::cout << "\n";
    }
}

// Print bounds
void PolygonGC::printBounds()  {
    std::cout << "Bounds:\n";
    std::cout << "  Min: "; m_minBounds.print(); std::cout << "\n";
    std::cout << "  Max: "; m_maxBounds.print(); std::cout << "\n";
}

// Print polygon color
void PolygonGC::printColor()  {
    std::cout << "Polygon color: implement me!!!!! ";
    // m_color;
    std::cout << "\n";
}
