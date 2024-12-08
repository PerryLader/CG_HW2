#ifndef	MODEL_H
#define	MODEL_H
#include "ObjectGC.h"
#include "Geometry.h"
#include "Renderer.h"
#include <vector>

class Model
{
protected:
	virtual ~Model() {};
	Model(const Geometry& T) : T(T) , mTransform(){};
	void virtual draw(Renderer& r) = 0;
	Geometry T;
	Matrix4 mTransform;
public:
	void virtual print() = 0;
	//std::vector<ObjectGC*> m_Objects;
	//void addObj(IPObjectStruct* obj, double color[3]);
	//void print();
};

#endif