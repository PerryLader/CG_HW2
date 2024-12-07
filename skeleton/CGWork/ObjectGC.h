#ifndef	OBJECTGC_H
#define	OBJECTGC_H
#include "Polygon.h"


class ObjectGC
{
public:
	std::string m_name;
	std::vector<PolygonGC*> m_polygons;
	ObjectGC(std::string name);
	void addPolygons(IPObjectStruct* obj, double color[3]);
	void print();
};

#endif