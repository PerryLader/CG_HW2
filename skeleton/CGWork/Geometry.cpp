#include "Geometry.h"

Geometry::Geometry(std::string name) : m_name(name) {}

// Destructor
Geometry::~Geometry() {
	for (PolygonGC* polygon : m_polygons) {
		delete polygon;
	}
	m_polygons.clear();
}

BBox Geometry::getBBox() const{
	return BBox();
}
std::string Geometry::getName() {
	return this->m_name;
}

void Geometry::addPolygon(PolygonGC* poli)
{
	this->m_polygons.push_back(poli);
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
		const std::vector<Line>* edges = poly.getEdges();
		res->insert(res->end(), edges->begin(), edges->end());
		delete edges;
	}
	return res;
}
void Geometry::backFaceCulling() {
    const Vector4 camera_vec = Vector4::unitZ();
	for (auto it = m_polygons.begin(); it != m_polygons.end(); ) {
		PolygonGC* polygon = *it;
		if (polygon->isBehindCamera() || Vector4::dot(camera_vec, polygon->getNormal()) < 0) {
			delete polygon;
			it = m_polygons.erase(it);
		}
		else
			it++;
	}
}

void Geometry::clip() {
	for (PolygonGC* temp : m_polygons)
		temp->clip();
}

void Geometry::print() const
{
	int i = 0;
	for (PolygonGC* temp : m_polygons)
	{
		std::cout << "		Polygon[" << i << "] vertices:" << std::endl;
		temp->printVertices();
		i++;
	}
}