#include "Renderer.h"
#include <cstring> // For memset

Renderer::Renderer(int width, int height) {
    createBuffers(width, height);
}

Renderer::~Renderer() {
    delete[] m_Buffer;
    delete[] m_ZBuffer;
}

void Renderer::addModel(const Model* geoModel) {
    m_models_to_render.push_back(geoModel);
}

#include "Renderer.h"
#include <iostream>
#include <algorithm> // For std::sort

void Renderer::render(const Camera* camera, int width, int height) {
    createBuffers(width, height);
    // Combine view and projection matrices
    const Matrix4 viewProjectionMatrix = camera->getViewMatrix() * camera->getProjectionMatrix();

    // Transform and cull geometry
    std::vector<Geometry*> transformedGeometries;
    for (const auto& model : m_models_to_render) {
        const Matrix4 transformation = model->getModelTransformation() * viewProjectionMatrix;
        Geometry* transformedGeometry = model->applyTransformation(transformation);
        // Clipping
        transformedGeometry->clip();
        // Backface culling
        transformedGeometry->backFaceCulling();

        transformedGeometries.push_back(transformedGeometry);
    }

    // Quantitative Visibility (Appel's algorithm)
    std::vector<Line> edges;
    for (const auto& geom : transformedGeometries) {
        const std::vector<Line>* geomEdges = geom->getEdges();
        edges.insert(edges.end(), geomEdges->begin(), geomEdges->end());
        delete geomEdges;
    }

    // Compute visibility for each edge
    for (auto& edge : edges) {
        edge.computeQuantitativeVisibility(transformedGeometries);
    }

    // Render visible edges
    for (const auto& edge : edges) {
        if (edge.isVisible()) {
            edge.draw();
        }
    }

    // Present the buffer (this is just an example, actual implementation may vary)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Output the pixel value (this is just an example, actual implementation may vary)
            std::cout << m_Buffer[(y * width + x) * 3] << " ";
        }
        std::cout << std::endl;
    }
}

void Renderer::clear() {
    if(m_Buffer) delete[] m_Buffer;
    if (m_ZBuffer) delete[] m_ZBuffer;
    m_Buffer = nullptr;
    m_ZBuffer = nullptr;
}

void Renderer::createBuffers(int width, int height) {
    clear();
    m_Buffer = new float[3 * width * height]; // RGB buffer
    m_ZBuffer = new float[width * height]; // Z-buffer
    std::memset(m_Buffer, 0, sizeof(float) * 3 * width * height);
    std::memset(m_ZBuffer, 0, sizeof(float) * width * height);
}
