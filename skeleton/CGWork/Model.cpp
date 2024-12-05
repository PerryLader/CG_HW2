#include "Model.h"
void Model::addObj(IPObjectStruct* obj, double color[3])
{
	for (ObjectGC temp:m_Objects)
	{
		if (temp.m_name == obj->ObjName)
		{
			temp.addPolygons(obj, color);
			return;
		}
	}
	//new Obj
	ObjectGC newObj(std::string(obj->ObjName));
	newObj.addPolygons(obj, color);
	m_Objects.push_back(newObj);
}