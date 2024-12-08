#ifndef	GEOMETRY_H
#define	GEOMETRY_H
#include "Polygon.h"

class Geometry
{
private:
	std::vector<PolygonGC*> m_polygons;
	std::string m_name;
public:
	std::string getName();
	Geometry(std::string name);
	BBox getBBox();
	void addPolygons(IPObjectStruct* obj, double color[3]);
	void Geometry::addPolygon(PolygonGC* poli);
	Geometry* applyTransformation(const Matrix4& tMat) const;
	void print();
};

#endif