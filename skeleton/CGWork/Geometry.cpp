#include "Geometry.h"

Geometry::Geometry(std::string name) : m_name(name) ,m_bBox(){}

// Destructor
Geometry::~Geometry() {
	for (PolygonGC* polygon : m_polygons) {
		delete polygon;
	}
	m_polygons.clear();
}

BBox Geometry::getBBox() const{
	return m_bBox;
}
std::string Geometry::getName() {
	return this->m_name;
}

void Geometry::addPolygon(PolygonGC* poli)
{
	this->m_polygons.push_back(poli);
	m_bBox.updateBBox(poli->getBbox());
}

Geometry* Geometry::applyTransformation(const Matrix4& tMat) const{
	Geometry* res = new Geometry(m_name);
	for (const auto& poly : m_polygons) {
		res->addPolygon(poly->applyTransformation(tMat));
	}
	return res;
}
std::vector<Line>* Geometry::getEdges() const {
	std::vector<Line>* res = new std::vector<Line>;
	for (const auto& poly : m_polygons) {
		const std::vector<Line>* edges = poly->getEdges();
		res->insert(res->end(), edges->begin(), edges->end());
		delete edges;
	}
	return res;
}

void Geometry::backFaceCulling() {
    const Vector3 camera_vec = Vector3::unitZ();
	for (auto it = m_polygons.begin(); it != m_polygons.end(); ) {
		PolygonGC* polygon = *it;
		if (polygon->isBehindCamera() || Vector3::dot(camera_vec, polygon->getNormal()) < 0) {
			delete polygon;
			it = m_polygons.erase(it);
		}
		else
			it++;
	}
}

std::vector<Line> Geometry::getPolyBboxLines(const ColorGC& bBoxColor)
{
	std::vector<Line> lines;
	for (auto t : m_polygons)
	{
		std::vector<Line> polyLines=t->getPolyBboxLine(bBoxColor);
		lines.insert(lines.end(), polyLines.begin(), polyLines.end());
	}
	return lines;
}

std::vector<Line> Geometry::calcPolyNormalLine(const ColorGC& normalColor)
{
	std::vector<Line> lines;
	for (auto t : m_polygons)
	{
		lines.push_back(t->calcNormalLine(normalColor));
	}
	return lines;
}

std::vector<Line> Geometry::getPolyNormalLineFromData(const ColorGC& normalColor)
{
	std::vector<Line> lines;
	for (auto t : m_polygons)
	{
		lines.push_back( t->getNormalLineFromData(normalColor));
	}
	return lines;
}

void Geometry::clip() {
	for (PolygonGC* temp : m_polygons)
		temp->clip();
}

void Geometry::print() const
{
	int i = 0;
	for (const PolygonGC* temp : m_polygons)
	{
		std::cout << "		Polygon[" << i << "] vertices:" << std::endl;
		temp->printVertices();
		i++;
	}
}