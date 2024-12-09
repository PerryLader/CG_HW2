#include "Polygon.h"

////////////////////////
//  do youw want us   //
//   to implement     //
//  matrix ops using  //
//      OpenCl??      //
////////////////////////

void BBox::toPrint() const{
    std::cout << "Boudning Box: " << m_minBounds <<", " << m_maxBounds << std::endl;
}

void BBox::updateBBox(const Vector4& vert) {
    m_minBounds.x = std::min(m_minBounds.x, vert.x);
    m_minBounds.y = std::min(m_minBounds.y, vert.y);
    m_minBounds.z = std::min(m_minBounds.z, vert.z);
    m_maxBounds.x = std::max(m_maxBounds.x, vert.x);
    m_maxBounds.y = std::max(m_maxBounds.y, vert.y);
    m_maxBounds.z = std::max(m_maxBounds.z, vert.z);
}

bool BBox::bboxCollide(const BBox& bbox) const{
    return BBox::bboxCollide(*this, bbox);
}
bool BBox::bboxCollide(const BBox& bbox1, const BBox& bbox2) {
    return false;
}
// Update min and max bounds
void PolygonGC::updateBounds(const Vertex& vert) {
    m_bbox.updateBBox(vert.location());
}

// reset min and max bounds
void PolygonGC::resetBounds() {
    if (m_vertices.empty()) {
        m_bbox = BBox();
        return;
    }
    m_bbox = BBox(Vector4(FLT_MAX, FLT_MAX, FLT_MAX, 1), Vector4(-FLT_MAX, -FLT_MAX, -FLT_MAX, 1));
    for (Vertex* vertex : m_vertices) {
        m_bbox.updateBBox(vertex->location());
    }
}


// Constructor with a default color
PolygonGC::PolygonGC(int R, int G, int B) : m_color(R, G, B, 0) {
    resetBounds();
}

PolygonGC::~PolygonGC(){
    for (Vertex* vert : m_vertices) {
        delete vert;
    }
    m_vertices.clear();
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
const Vector4& PolygonGC::getColor() {
    return m_color;
}

// Add a vertex
void PolygonGC::addVertexs(IPVertexStruct* vertex) {
    while (vertex)
    {
        Vertex* temp = new Vertex(Vector4(
            vertex->Coord[0],
            vertex->Coord[1],
            vertex->Coord[2], 1));
        m_vertices.push_back(temp);
        updateBounds(*temp);
        vertex = vertex->Pnext;
    }
}

void PolygonGC::addVertex(Vertex* vertex) {
    if (vertex)
    {
        m_vertices.push_back(vertex);
        updateBounds(*vertex);
    }
}

// Get the number of vertices
size_t PolygonGC::vertexCount() {
    return m_vertices.size();
}


// Print all vertices
void PolygonGC::printVertices() {

    for (size_t i = 0; i < m_vertices.size(); ++i) {
        std::cout << "                  Vertex[" << i << "]: ";
        m_vertices[i]->print(); // Assuming Vertex has a `print` method
        std::cout << "\n";
    }
}

// Print bounds
void PolygonGC::printBounds() {
    m_bbox.toPrint();
}

// Print polygon color
void PolygonGC::printColor() {
    std::cout << "Polygon color: implement mme!!!!! ";
    // m_color;
    std::cout << "\n";
}

// Function to apply a transformation matrix to all vertices
PolygonGC* PolygonGC::applyTransformation(const Matrix4& transformation) const{
    PolygonGC* newPoly = new PolygonGC(this->m_color.x , this->m_color.y, this->m_color.z);
    for (const Vertex* vertex : m_vertices) {
       // Vertex* newVertex = new Vertex(transformation * vertex);
       // newPoly->addVertex(newVertex);
    }
    return newPoly;
}

// get polygon Bbox
BBox PolygonGC::getBbox() {
    return BBox();
}