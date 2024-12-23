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
    // Check for overlap along the x-axis
    bool xOverlap = (bbox1.m_minBounds.x <= bbox2.m_maxBounds.x) && (bbox1.m_maxBounds.x >= bbox2.m_minBounds.x);

    // Check for overlap along the y-axis
    bool yOverlap = (bbox1.m_minBounds.y <= bbox2.m_maxBounds.y) && (bbox1.m_maxBounds.x >= bbox2.m_minBounds.x);

    // Check for overlap along the z-axis
    bool zOverlap = (bbox1.m_minBounds.z <= bbox2.m_maxBounds.z) && (bbox1.m_maxBounds.x >= bbox2.m_minBounds.x);

    // Bounding boxes collide if they overlap along all three axes
    return xOverlap && yOverlap && zOverlap;
}
BBox BBox::transformBBox(const Matrix4& tmat) const {
    Vector3 transformedMin = (tmat * Vector4::extendOne(m_minBounds)).toVector3();
    Vector3 transformedMax = (tmat * Vector4::extendOne(m_maxBounds)).toVector3();
    BBox res;
    res.updateBBox(transformedMin);
    res.updateBBox(transformedMax);
    return res;
}
//void BBox::updateBBox(const BBox& box)
//{
//    updateBBox(box.m_maxBounds);
//    updateBBox(box.m_minBounds);
//}
std::vector<Line> BBox::getLinesOfBbox(const ColorGC& bBoxColor) const
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

void PolygonGC::setCalcAndDataNormalLines( Vector3 dataNormal)
{
    Vector3 centerPoint(0, 0, 0);
    for (const auto& v : m_vertices)
    {
        centerPoint += v->loc();
    }
    centerPoint /= m_vertices.size();
    m_calcNormalLine= Line(centerPoint, centerPoint + (calculateNormal().normalized() * 0.25),m_color);
    m_dataNormalLine = Line(centerPoint, centerPoint + (dataNormal.normalized() * 0.25), m_color);
}

void PolygonGC::setCalcNormalLines()
{
    Vector3 centerPoint(0, 0, 0);
    for (const auto& v : m_vertices)
    {
        centerPoint += v->loc();
    }
    centerPoint /= m_vertices.size();
    m_calcNormalLine = Line(centerPoint, centerPoint + (calculateNormal().normalized() * 0.25));
    m_hasDataNormal = false;
}

Vector3 PolygonGC::getCalcNormalNormolized()
{
    return (m_calcNormalLine.m_b - m_calcNormalLine.m_a).normalized();
}

Vector3 PolygonGC::getDataNormalNormolized()
{
    if (!hasDataNormalLine())
    {
        throw std::exception();
    }
    return (m_dataNormalLine.m_b - m_dataNormalLine.m_a).normalized();;
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

void PolygonGC::addVertex(std::shared_ptr<Vertex> vertex) {
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
PolygonGC* PolygonGC::applyTransformation(const Matrix4& transformation) const
{
    PolygonGC* newPoly = new PolygonGC(this->m_color);
    for (auto vertex : m_vertices) {
        newPoly->addVertex(vertex->getTransformedVertex(transformation));
    }

    newPoly->m_calcNormalLine = this->m_calcNormalLine.getTransformedLine(transformation);
    if (newPoly->m_hasDataNormal)
    {
        newPoly->m_dataNormalLine = this->m_dataNormalLine.getTransformedLine(transformation);
    }
    return newPoly;
}

std::vector<Line> PolygonGC::getPolyBboxLine(const ColorGC* overridingColor)
{
    return m_bbox.getLinesOfBbox(overridingColor == nullptr ? m_color : *overridingColor);
}
static bool ifEdgeBBOXCutUnitCube(const Vertex& v1, const Vertex& v2) {
    BBox b;
    b.updateBBox(v1.loc());
    b.updateBBox(v2.loc());
    BBox unit = BBox::unitBBox();
    return BBox::bboxCollide(b, unit);
}
std::vector<Line>* PolygonGC::getEdges(const ColorGC* overridingColor) const {
    std::vector<Line>* edges = new std::vector<Line>();
    ColorGC line_color = overridingColor == nullptr ? m_color : *overridingColor;
    for (size_t i = 0; i < m_vertices.size(); ++i) {
        std::shared_ptr<Vertex> v1 = m_vertices[i];
        std::shared_ptr<Vertex> v2 = m_vertices[(i + 1) % m_vertices.size()];
        if(ifEdgeBBOXCutUnitCube(*v1, *v2))
            edges->push_back(Line(v1->loc(), v2->loc(), line_color));
    }
    return edges;
}

// get polygon Bbox
BBox PolygonGC::getBbox() const{
    return m_bbox;
}

Line PolygonGC::getCalcNormalLine(const ColorGC* overridingColor) const
{
    return Line(m_calcNormalLine.m_a, m_calcNormalLine.m_b, overridingColor == nullptr ? m_calcNormalLine.m_color : *overridingColor);

}

Line PolygonGC::getDataNormalLine(const ColorGC* overridingColor) const
{
    if (!hasDataNormalLine())
    {
        throw std::exception();
    }

    return Line(m_dataNormalLine.m_a, m_dataNormalLine.m_b, overridingColor == nullptr ? m_dataNormalLine.m_color : *overridingColor);
}

bool PolygonGC::hasDataNormalLine() const{
    return m_hasDataNormal;
}


std::vector<Line>* PolygonGC::getVertNormLinesFromData(const ColorGC* overridingColor)const {
    std::vector<Line>* normalLines = new std::vector<Line>();
    for (const auto& vert : m_vertices) {
        try {
            normalLines->push_back(vert->getDataNormalLine());
        }
        catch (...) {
            normalLines->clear();
            delete normalLines;
            throw std::exception();
        }
    }
    return normalLines;
}
std::vector<Line>* PolygonGC::getVertNormLinesFromCalc(const ColorGC* overridingColor) const {
    std::vector<Line>* normalLines = new std::vector<Line>();
    for (const auto& vert : m_vertices) {
        normalLines->push_back(vert->getCalcNormalLine());
    }
    return normalLines;
}

Vector3 PolygonGC::calculateNormal() const {
    if (m_vertices.size() < 3)
    {
        throw std::runtime_error("whaht the hell just happend?is it polygon with less then 2 vertices???hemmm?");
    }
    const Vector3 vec1 = m_vertices.at(1)->loc() - m_vertices.at(0)->loc();
    const Vector3 vec2 = m_vertices.at(2)->loc() - m_vertices.at(1)->loc();
    return Vector3::cross(vec2, vec1).normalized();

}