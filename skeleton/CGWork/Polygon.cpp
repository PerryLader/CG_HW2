#include "Polygon.h"

/////////////////////////////
//  do youw want us        //
//   to implement          //
//  matrix ops using       //
//      OpenCl?? answer    //
//    yes my man!BJ also?  //
// Yes my friend! coffee?  //
/////////////////////////////

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
    m_bbox.updateBBox(vert.loc());
}

// reset min and max bounds
void PolygonGC::resetBounds() {
    if (m_vertices.empty()) {
        m_bbox = BBox();
        return;
    }
    m_bbox = BBox(Vector4(FLT_MAX, FLT_MAX, FLT_MAX, 1), Vector4(-FLT_MAX, -FLT_MAX, -FLT_MAX, 1));
    for (Vertex* vertex : m_vertices) {
        m_bbox.updateBBox(vertex->loc());
    }
}
std::vector<Vertex*> m_vertices; // List of vertices
Vector4 m_color;                // Color of the polygon
Vector4 m_nomal;                // Color of the polygon
BBox m_bbox;
// Update min and max bounds
bool m_hasNormal;

// Constructor with a default color
PolygonGC::PolygonGC(int R, int G, int B) : m_color(R, G, B, 0), m_hasNormal(false){
    resetBounds();
}
PolygonGC::PolygonGC(const Vector4& normal,int R = 0, int G = 0, int B = 0) : m_color(R, G, B, 0),m_nomal(normal),m_hasNormal(true){
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
const Vector4& PolygonGC::getColor() const{
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
size_t PolygonGC::vertexCount() const{
    return m_vertices.size();
}


// Print all vertices
void PolygonGC::printVertices() const{

    for (size_t i = 0; i < m_vertices.size(); ++i) {
        std::cout << "                  Vertex[" << i << "]: ";
        m_vertices.at(i)->print();
        std::cout << "\n";
    }
}

// Print bounds
void PolygonGC::printBounds() const{
    m_bbox.toPrint();
}

bool PolygonGC::isBehindCamera() const{
    for (size_t i = 0; i < m_vertices.size(); ++i)
        if (m_vertices[i]->loc().z > 0)
            return false;
    return true;
}
// Print polygon color
void PolygonGC::printColor() const{
    std::cout << "Polygon color: implement mme!!!!! ";
    // m_color;
    std::cout << "\n";
}

void PolygonGC::clip(){
    std::set<Vertex*> outscopeVertices;
    std::vector<Vertex*> inscopeVertices;
    for (size_t i = 0; i < m_vertices.size(); ++i) {
        Vertex* v1 = m_vertices[i];
        Vertex* v2 = m_vertices[(i + 1) % m_vertices.size()];

        // Check if vertices are inside the clipping volume
        bool v1Inside = v1->isInsideClipVolume();
        bool v2Inside = v2->isInsideClipVolume();

        if (v1Inside && v2Inside) {
            // Both vertices are inside, add v2 to the clipped vertices
            inscopeVertices.push_back(v2);
        }
        else if (v1Inside && !v2Inside) {
            // v1 is inside, v2 is outside, add intersection point

            inscopeVertices.push_back(intersectClipVolume(v1, v2));
            outscopeVertices.insert(v2);
        }
        else if (!v1Inside && v2Inside) {
            // v1 is outside, v2 is inside, add intersection point and v2
            inscopeVertices.push_back(intersectClipVolume(v1, v2));
            inscopeVertices.push_back(v2);
            outscopeVertices.insert(v1);
        }
    }
    for (auto& elem : outscopeVertices) {
        delete elem;
    }
    m_vertices = inscopeVertices;
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
BBox PolygonGC::getBbox() const{
    return BBox();
}

Vector4 PolygonGC::getNormal() const
{
    return m_nomal;
}

bool PolygonGC::hasNormal() const{
    return m_hasNormal;
}

void PolygonGC::calculateNormal() {
    if (m_vertices.size() < 3)
    {
        throw std::runtime_error("whaht the hell just happend?is it polygon with less then 2 vertices???hemmm?");
    }
    const Vector4 vec1 = m_vertices.at(1)->loc() - m_vertices.at(0)->loc();
    const Vector4 vec2 = m_vertices.at(2)->loc() - m_vertices.at(1)->loc();
    m_nomal = Vector4::cross(vec1, vec2);

}