#include "Renderer.h"
#include <cstring> // For memset
#include <iostream>
#include <algorithm> // For std::sort

Renderer::Renderer():m_Buffer(nullptr),m_ZBuffer(nullptr),m_shader(nullptr){
   
}

Renderer::~Renderer() {
    delete[] m_Buffer;
    delete[] m_ZBuffer;
}

//void Renderer::addModel(const Model* geoModel) {
//    m_models_to_render.push_back(geoModel);
//}



void Renderer::render(const Camera* camera, int width, int height,const std::vector<Model*> m_models, const ColorGC& bgColor) {
    createBuffers(bgColor, width, height);
    // Combine view and projection matrices
    const Matrix4 viewProjectionMatrix = Matrix4::identity(); //camera->getViewMatrix() * camera->getProjectionMatrix();

    // Transform and cull geometry
    std::vector<Geometry*> transformedGeometries;
    for (const auto& model : m_models) {
        const Matrix4 transformation = model->getModelTransformation() * viewProjectionMatrix;
        Geometry* transformedGeometry = model->applyTransformation(transformation);

        // Clipping
        transformedGeometry->clip();
        // Backface culling
        transformedGeometry->backFaceCulling();

        transformedGeometries.push_back(transformedGeometry);
    }

   
    std::vector<Line> edges;
    for (const auto& geom : transformedGeometries) {
        const std::vector<Line>* geomEdges = geom->getEdges();
        edges.insert(edges.end(), geomEdges->begin(), geomEdges->end());
        delete geomEdges;
    }

#ifdef APPLE_ALGO
    for (auto& edge : edges) {
        edge.computeQuantitativeVisibility(transformedGeometries);
    }
#endif // APPLE_ALGO

    // Compute visibility for each edge
   

    // Render visible edges
    for ( Line& edge : edges) {
       // if (edge.isVisible()) {
            edge.draw(m_Buffer,width,height);
       // }
    }

    // Present the buffer (this is just an example, actual implementation may vary)
    //for (int y = 0; y < height; ++y) {
    //    for (int x = 0; x < width; ++x) {
    //        // Output the pixel value (this is just an example, actual implementation may vary)
    //        std::cout << m_Buffer[(y * width + x) * 3] << " ";
    //    }
    //    std::cout << std::endl;
    //}
}

void Renderer::clear() {
    if(m_Buffer!=nullptr) delete[] m_Buffer;
    if (m_ZBuffer != nullptr) delete[] m_ZBuffer;
    m_Buffer = nullptr;
    m_ZBuffer = nullptr;
}
uint32_t* Renderer::getBuffer() {
    return m_Buffer;
}
void Renderer::createBuffers(const ColorGC& bg_color, int width, int height) {
    clear();
    m_Buffer = new uint32_t[width * height]; // RGB buffer
    m_ZBuffer = new float[width * height]; // Z-buffer
    std::memset(m_Buffer,100, sizeof(uint32_t) *  width * height);
    std::memset(m_ZBuffer, 0, sizeof(float) * width * height);
}
//
//void Renderer::fillBackgroundColor(const ColorGC& bg_color) {
//    const auto& color = bg_color.getRGBA();
//    std::memset(m_Buffer, 0, sizeof(color) * 4 * width * height);
//}

