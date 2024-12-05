#include "ObjectGC.h"

ObjectGC::ObjectGC(std::string name) : m_name(name){}



void ObjectGC::addPolygons(IPObjectStruct* obj, double color[3])
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
void ObjectGC::print()
{
	int i = 0;
	for (PolygonGC temp : m_polygons)
	{
		std::cout << "Obj name:" << m_name << std::endl << "Polygons:" << std::endl;
		std::cout << "Polygon[" << i<<"]=";
		temp.printVertices();
	}
}