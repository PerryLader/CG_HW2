#include "Model.h"
void Model::addObj(IPObjectStruct* obj, double color[3])
{
	for (ObjectGC* temp:m_Objects)
	{
		if (temp->m_name == obj->ObjName)
		{
			temp->addPolygons(obj, color);
			return;
		}
	}
	//new Obj
	ObjectGC *newObj=new ObjectGC(std::string(obj->ObjName));
	newObj->addPolygons(obj, color);
	m_Objects.push_back(newObj);
}
void Model::print()
{
	int i = 0;
	for (ObjectGC *temp : m_Objects)
	{
		std::cout << "Obj["<<i<<"] name:" << temp->m_name << std::endl << "	Polygons : "<< std::endl;
		temp->print();
		i++;
	}
	
}