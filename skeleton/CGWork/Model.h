#pragma once
#include "Polygon.h"
#include "iritprsr.h"


class Model
{
public:
	std::vector<PolygonGC> m_polygons;

	void addPolygon(IPPolygonStruct* p, double color[3]);
};

