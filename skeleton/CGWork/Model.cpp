#include "Model.h"
void Model::addPolygon(IPPolygonStruct* p, double color[3])
{
	PolygonGC newPoly(color[0], color[1], color[2]);
	IPVertexStruct* tempVertex = p->PVertex;
	while (tempVertex)
	{
		newPoly.addVertex(Vertex(Vector4(tempVertex->Coord[0], tempVertex->Coord[1], tempVertex->Coord[2], 1)));
		tempVertex = tempVertex->Pnext;
	}
	m_polygons.push_back(newPoly);
}