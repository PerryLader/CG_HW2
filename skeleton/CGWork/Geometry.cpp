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
	Geometry* res = new Geometry(this->m_name);
	for (const auto& poly : this->m_polygons) {
		res->addPolygon(poly->applyTransformation(tMat));
	}
	return res;
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