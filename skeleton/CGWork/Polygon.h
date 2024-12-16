#pragma once
#include "Vertex.h"
#include <iostream>
#include <vector>
#include <limits>
#include <windef.h>
#include <wingdi.h>
#include <cfloat>
//#include <algorithm>

class PolygonGC {
    std::vector<Vertex> m_vertices; // List of vertices
    COLORREF m_color;                // Color of the polygon
    Vector4 m_minBounds;            // Minimum bounds
    Vector4 m_maxBounds;            // Maximum bounds

    // Update min and max bounds
    void updateBounds() {
        if (m_vertices.empty()) {
            m_minBounds = Vector4();
            m_maxBounds = Vector4();
            return;
        }

        m_minBounds = Vector4(FLT_MAX, FLT_MAX, FLT_MAX,1);
        m_maxBounds = Vector4(-FLT_MAX, -FLT_MAX, -FLT_MAX, 1);

        for (const auto& vertex : m_vertices) {
            const auto& pos = vertex.m_point; // Assuming Vertex has a `position` member
            m_minBounds.x = min(m_minBounds.x, pos.x);
            m_minBounds.y = min(m_minBounds.y, pos.y);
            m_minBounds.z = min(m_minBounds.z, pos.z);
            //m_minBounds.w = min(m_minBounds.w, pos.w);

            m_maxBounds.x = max(m_maxBounds.x, pos.x);
            m_maxBounds.y = max(m_maxBounds.y, pos.y);
            m_maxBounds.z = max(m_maxBounds.z, pos.z);
           // m_maxBounds.w = max(m_maxBounds.w, pos.w);
        }
    }

public:
    // Constructor with a default color
    PolygonGC(int R = 0,int G = 0,int B=0) : m_color(RGB(R,G,B)) {
        updateBounds();
    }

    // Set the color of the polygon
    void setColor(const COLORREF& newColor) {
        m_color = newColor;
    }

    // Get the color of the polygon
    const Vector4& getColor() const {
        return m_color;
    }

    // Add a vertex
    void addVertex(const Vertex& vertex) {
        m_vertices.push_back(vertex);
        updateBounds();
    }

    

    // Get the number of vertices
    size_t vertexCount() const {
        return m_vertices.size();
    }


    // Print all vertices
    void printVertices(){
        std::cout << "Polygon vertices:\n";
        for (size_t i = 0; i < m_vertices.size(); ++i) {
            std::cout << "  Vertex " << i + 1 << ": ";
            m_vertices[i].print(); // Assuming Vertex has a `print` method
            std::cout << "\n";
        }
    }

    // Print bounds
    void printBounds() const {
        std::cout << "Bounds:\n";
        std::cout << "  Min: "; m_minBounds.print(); std::cout << "\n";
        std::cout << "  Max: "; m_maxBounds.print(); std::cout << "\n";
    }

    // Print polygon color
    void printColor() const {
        std::cout << "Polygon color: implement me!!!!! ";
       // m_color;
        std::cout << "\n";
    }
};
