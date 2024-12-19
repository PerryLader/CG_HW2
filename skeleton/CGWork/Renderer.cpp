#include "Renderer.h"
#include <cstring> // For memset
#include <iostream>
#include <algorithm> // For std::sort

Renderer::Renderer():m_Buffer(nullptr),
m_ZBuffer(nullptr),
m_BgBuffer(nullptr),
m_shader(nullptr),
m_bgColor(),
m_width(0),
m_height(0){}

Renderer::~Renderer() {
    clear(true);
}

//void Renderer::addModel(const Model* geoModel) {
//    m_models_to_render.push_back(geoModel);
//}



void Renderer::render(const Camera* camera, int width, int height,const std::vector<Model*> models, const ColorGC& bgColor) {
    if (getWidth() != width || getHeight() != height || getBgColor().getARGB() != bgColor.getARGB()) {
        setWidth(width); setHeight(height); setBgColor(bgColor);
        refreshBgBuffer();
    }
    createBuffers();
    memcpy(m_Buffer, m_BgBuffer, sizeof(uint32_t)*width*height);
    // Combine view and projection matrices

    float aspectRatio = width / height;
    Matrix4 aspectRatioMatrix = Matrix4::scaling(Vector3(1.0f / aspectRatio, 1.0f, 1.0f));
    const Matrix4 viewProjectionMatrix = camera->getViewMatrix() * aspectRatioMatrix * camera->getProjectionMatrix();

    // Transform and cull geometry
    std::vector<Geometry*> transformedGeometries;
    for (const auto& model : models) {
        const Matrix4 transformation = model->getModelTransformation() * viewProjectionMatrix;
        Geometry* transformedGeometry = model->applyTransformation(transformation);

        // Clipping
        transformedGeometry->clip();
        // Backface culling
        //transformedGeometry->backFaceCulling();//there is bug here

        transformedGeometries.push_back(transformedGeometry);
    }

   
    std::vector<Line> edges;
    //add axis origin for tests:
    edges.push_back(Line((viewProjectionMatrix * Vector4(-1, 0, 0,1)).toVector3(), (viewProjectionMatrix * Vector4(1, 0, 0, 1)).toVector3(), ColorGC(255, 0, 0)));
    edges.push_back(Line((viewProjectionMatrix * Vector4(0, -1, 0, 1)).toVector3(), (viewProjectionMatrix * Vector4(0, 1, 0, 1)).toVector3(), ColorGC(0, 255, 0)));
    edges.push_back(Line((viewProjectionMatrix * Vector4(0, 0, -1, 1)).toVector3(), (viewProjectionMatrix * Vector4(0, 0, 1, 1)).toVector3(), ColorGC(0, 0, 255)));

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

void Renderer::clear(bool clearBgBuffer) {
    delete[] m_Buffer;
    m_Buffer = nullptr;
    delete[] m_ZBuffer;
    m_ZBuffer = nullptr;
    if (clearBgBuffer) {
        delete[] m_BgBuffer;
        m_BgBuffer = nullptr;
    }
}
uint32_t* Renderer::getBuffer() const{
    return m_Buffer;
}
void Renderer::createBuffers() {
    clear(false);
    m_Buffer = new uint32_t[m_width * m_height]; // RGB buffer
    m_ZBuffer = new float[m_width * m_height]; // Z-buffer
    std::memset(m_ZBuffer, 0, sizeof(float) * m_width * m_height);
    std::memset(m_Buffer, 0, sizeof(uint32_t) * m_width * m_height);
}
void Renderer::refreshBgBuffer() {
    delete[] m_BgBuffer;
    m_BgBuffer = new uint32_t[m_width * m_height]; // background RGB buffer
    for (int i = 0; i < m_width; i++)
        for (int j = 0; j < m_height; j++)
            m_BgBuffer[i + j*m_width] = m_bgColor.getARGB();
}

//
//void Renderer::fillBackgroundColor(const ColorGC& bg_color) {
//    const auto& color = bg_color.getRGBA();
//    std::memset(m_Buffer, 0, sizeof(color) * 4 * width * height);
//}

