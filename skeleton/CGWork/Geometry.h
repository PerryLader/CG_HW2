#ifndef	GEOMETRY_H
#define	GEOMETRY_H
#include "Polygon.h"
#include <vector>
#include <string>

class Geometry
{
private:
	std::vector<PolygonGC*> m_polygons;
	std::string m_name;
public:
	std::string getName();
	Geometry(std::string name);
	BBox getBBox() const;
	void Geometry::addPolygon(PolygonGC* poli);
	Geometry* applyTransformation(const Matrix4& tMat) const;
	std::vector<Line>* getEdges() const;
	void backFaceCulling();
	void clip();
	void print() const;
	~Geometry();
};

#endif