#include "Geometry.h"

Geometry::Geometry(std::string name) : m_name(name) {}

BBox Geometry::getBBox() {
	return BBox();
}
std::string Geometry::getName() {
	return this->m_name;
}

void Geometry::addPolygons(IPObjectStruct* obj, double color[3])
{
	//PolygonGC newPoly(color[0], color[1], color[2]);
	IPVertexStruct* tempVertex;
	IPPolygonStruct* p = obj->U.Pl;
	while (p)
	{
		PolygonGC* newPoly = new PolygonGC(color[0], color[1], color[2]);
		newPoly->addVertexs(p->PVertex);
		this->m_polygons.push_back(newPoly);
		p = p->Pnext;
	}
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

void Geometry::print()
{
	int i = 0;
	for (PolygonGC* temp : m_polygons)
	{
		std::cout << "		Polygon[" << i << "] vertices:" << std::endl;
		temp->printVertices();
		i++;
	}
}