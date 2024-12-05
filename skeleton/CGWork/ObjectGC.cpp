#include "ObjectGC.h"

ObjectGC::ObjectGC(std::string name) : m_name(name){}
void addPolygons(IPObjectStruct* obj, double color[3])
{
	//PolygonGC newPoly(color[0], color[1], color[2]);
	IPVertexStruct* tempVertex;
	IPPolygonStruct* p= obj->U.Pl;
	while (p)
	{
		PolygonGC newPoly(color[0], color[1], color[2]);
		newPoly.addVertexs(p->PVertex);
		
		p = p->Pnext;
	}
}