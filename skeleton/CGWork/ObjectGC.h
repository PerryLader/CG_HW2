#ifndef	OBJECTGC_H
#define	OBJECTGC_H
#include "Polygon.h"



class ObjectGC
{
private:
	std::vector<PolygonGC*> m_polygons;
	std::string m_name;
public:
	std::string getName();
	ObjectGC(std::string name);
	BBox getBBox();
	void addPolygons(IPObjectStruct* obj, double color[3]);
	void print();
};

#endif