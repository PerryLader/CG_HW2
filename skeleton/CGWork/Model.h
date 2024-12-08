#ifndef	MODEL_H
#define	MODEL_H
#include "ObjectGC.h"
#include <vector>

class Model
{
public:
	std::vector<ObjectGC*> m_Objects;
	void addObj(IPObjectStruct* obj, double color[3]);
	void print();
};

#endif