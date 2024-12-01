#pragma once
#include "Polygon.h"
#include "iritprsr.h"
#define WINDOWS_IGNORE_PACKING_MISMATCH


class Model
{
public:
	std::vector<PolygonGC> m_polygons;

	void addPolygon(IPPolygonStruct* p, double color[3])
	{
		PolygonGC newPoly(color[0], color[1], color[2]);
		IPVertexStruct *tempVertex = p->PVertex;
		while (tempVertex)
		{
			newPoly.addVertex(Vertex(Vector4(tempVertex->Coord[0], tempVertex->Coord[1], tempVertex->Coord[2], 1)));
			tempVertex = tempVertex->Pnext;
		}
	}
};

