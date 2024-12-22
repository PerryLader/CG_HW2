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

void BBox::updateBBox(const Vector3& vert) {
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
    return false;//TODO
}
void BBox::updateBBox(const BBox& box)
{
    updateBBox(box.m_maxBounds);
    updateBBox(box.m_minBounds);
}
std::vector<Line> BBox::getLinesOfBbox( const ColorGC& bBoxColor)
{
    Vector3 corners[8] = {
       {m_minBounds.x, m_minBounds.y, m_minBounds.z},
       {m_minBounds.x, m_minBounds.y, m_maxBounds.z},
       {m_minBounds.x, m_maxBounds.y, m_minBounds.z},
       {m_minBounds.x, m_maxBounds.y, m_maxBounds.z},
       {m_maxBounds.x, m_minBounds.y, m_minBounds.z},
       {m_maxBounds.x, m_minBounds.y, m_maxBounds.z},
       {m_maxBounds.x, m_maxBounds.y, m_minBounds.z},
       {m_maxBounds.x, m_maxBounds.y, m_maxBounds.z}
    };
    std::vector<Line> lines = {
        // Bottom face
        {corners[0], corners[1],bBoxColor},
        {corners[1], corners[5],bBoxColor},
        {corners[5], corners[4],bBoxColor},
        {corners[4], corners[0],bBoxColor},

        // Top face
        {corners[2], corners[3],bBoxColor},
        {corners[3], corners[7],bBoxColor},
        {corners[7], corners[6],bBoxColor},
        {corners[6], corners[2],bBoxColor},

        // Vertical edges
        {corners[0], corners[2],bBoxColor},
        {corners[1], corners[3],bBoxColor},
        {corners[4], corners[6],bBoxColor},
        {corners[5], corners[7],bBoxColor}
    };
    return lines;

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
    m_bbox = BBox(Vector3(FLT_MAX, FLT_MAX, FLT_MAX), Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX));
    for (auto vertex : m_vertices) {
        m_bbox.updateBBox(vertex->loc());
    }
}

// Constructor with a default color
PolygonGC::PolygonGC(ColorGC color) : m_color(color), m_hasDataNormal(false){
    resetBounds();
}
PolygonGC::PolygonGC(const Vector3& normal,ColorGC color) : m_color(color),m_dataNormal(normal),m_hasDataNormal(true){
    resetBounds();
}



// Set the color of the polygon
void PolygonGC::setColor(const ColorGC& newColor) {   
    m_color = newColor;
}

// Get the color of the polygon
const ColorGC& PolygonGC::getColor() const
{
    return m_color;
}

// Add a vertex
void PolygonGC::addVertexs(IPVertexStruct* vertex) {
    while (vertex)
    {
        std::shared_ptr<Vertex> temp(new Vertex(Vector3(
            vertex->Coord[0],
            vertex->Coord[1],
            vertex->Coord[2])));
        m_vertices.push_back(temp);
        updateBounds(*temp);
        vertex = vertex->Pnext;
    }
    if (3>m_vertices.size())
    {
        throw;
    }
    m_calcNormal= this->calculateNormal();
}

void PolygonGC::addVertex(std::shared_ptr<Vertex> vertex) {
    if (vertex)
    {
        m_vertices.push_back(vertex);
        if (m_vertices.size() == 3)
        {
            this->m_calcNormal = this->calculateNormal();
        }
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
std::vector<std::shared_ptr<Vertex>> PolygonGC::getVertexVector() 
{    
    return m_vertices;
}
// Print polygon color
void PolygonGC::printColor() const{
    std::cout << m_color.toHex();   
}

void PolygonGC::clip(){
    //std::set<Vertex*> outscopeVertices;
    //std::vector<Vertex*> inscopeVertices;
    //for (size_t i = 0; i < m_vertices.size(); ++i) {
    //    Vertex* v1 = m_vertices[i];
    //    Vertex* v2 = m_vertices[(i + 1) % m_vertices.size()];

    //    // Check if vertices are inside the clipping volume
    //    bool v1Inside = v1->isInsideClipVolume();
    //    bool v2Inside = v2->isInsideClipVolume();

    //    if (v1Inside && v2Inside) {
    //        // Both vertices are inside, add v2 to the clipped vertices
    //        inscopeVertices.push_back(v2);
    //    }
    //    else if (v1Inside && !v2Inside) {
    //        // v1 is inside, v2 is outside, add intersection point 
    //      //  inscopeVertices.push_back(Vertex::intersectClipVolume(v1, v2));
    //        outscopeVertices.insert(v2);
    //    }
    //    else if (!v1Inside && v2Inside) {
    //        // v1 is outside, v2 is inside, add intersection point and v2
    //        
    //    //    inscopeVertices.push_back(Vertex::intersectClipVolume(v1, v2));
    //        inscopeVertices.push_back(v2);
    //        outscopeVertices.insert(v1);
    //    }
    //}
    //for (auto& elem : outscopeVertices) {
    //    delete elem;
    //}
    //m_vertices = inscopeVertices;
}
// Function to apply a transformation matrix to all vertices
PolygonGC* PolygonGC::applyForceTransformation(const Matrix4& transformation) const
{
    PolygonGC* newPoly = new PolygonGC(this->m_color);
    for (auto vertex : m_vertices) {
        newPoly->addVertex(vertex->getTransformedVertex(transformation));
    }

    newPoly->m_calcNormal = (transformation * Vector4::extendOne(newPoly->m_calcNormal)).toVector3();
    if (newPoly->m_hasDataNormal)
    {
        newPoly->m_dataNormal = (transformation * Vector4::extendOne(newPoly->m_dataNormal)).toVector3();
    }
    return newPoly;
}
PolygonGC* PolygonGC::applySoftTransformation(const Matrix4& transformation) const{
    PolygonGC* newPoly = new PolygonGC(this->m_color);
    for ( auto vertex : m_vertices) {
       
            std::shared_ptr<Vertex> newVertex = vertex->getTransformedVertex(transformation);
            newPoly->addVertex(newVertex);
    }

    newPoly->m_calcNormal = (transformation * Vector4::extendOne(newPoly->m_calcNormal)).toVector3();
    if (newPoly->m_hasDataNormal)
    {
        newPoly->m_dataNormal = (transformation * Vector4::extendOne(newPoly->m_dataNormal)).toVector3();
    }
    return newPoly;
}
std::vector<Line> PolygonGC::getPolyBboxLine(const ColorGC& bBoxColor)
{
    return m_bbox.getLinesOfBbox(bBoxColor);
}

std::vector<Line>* PolygonGC::getEdges() const {
    std::vector<Line>* edges = new std::vector<Line>();
    for (size_t i = 0; i < m_vertices.size(); ++i) {
        std::shared_ptr<Vertex> v1 = m_vertices[i];
        std::shared_ptr<Vertex> v2 = m_vertices[(i + 1) % m_vertices.size()];
        edges->push_back(Line(*v1, *v2, m_color));
    }
    return edges;
}

// get polygon Bbox
BBox PolygonGC::getBbox() const{
    return m_bbox;
}

Vector3 PolygonGC::getCalcNormal() const
{
    return m_calcNormal;
}

Vector3 PolygonGC::getDataNormal() const
{
    return m_dataNormal;
}

bool PolygonGC::hasDataNormal() const{
    return m_hasDataNormal;
}
Line PolygonGC::calcNormalLine(ColorGC normalColor) const
{
    Vector3 centerPoint(0, 0, 0);
    for (auto t : m_vertices)
    {
        centerPoint = centerPoint + t->loc();
    }
    centerPoint = centerPoint * (1.0 / m_vertices.size());
    return Line(centerPoint, centerPoint + (m_calcNormal.normalized() * 0.25), normalColor);
}

Line PolygonGC::getNormalLineFromData(ColorGC normalColor) const
{
    if (!hasDataNormal())
    {
        std::cout << "U cant to ittt!!!!!!!!";
        throw;
    }
    Vector3 centerPoint(0, 0, 0);
    for (auto t : m_vertices)
    {
        centerPoint = centerPoint + t->loc();
    }
    centerPoint = centerPoint * (1 / m_vertices.size());
    return Line(centerPoint, centerPoint + m_dataNormal.normalized(), normalColor);

}
Vector3 PolygonGC::calculateNormal() const {
    if (m_vertices.size() < 3)
    {
        throw std::runtime_error("whaht the hell just happend?is it polygon with less then 2 vertices???hemmm?");
    }
    const Vector3 vec1 = m_vertices.at(1)->loc() - m_vertices.at(0)->loc();
    const Vector3 vec2 = m_vertices.at(2)->loc() - m_vertices.at(1)->loc();
    return Vector3::cross(vec1, vec2).normalized();

}