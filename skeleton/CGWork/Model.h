#ifndef	MODEL_H
#define	MODEL_H

#include "Geometry.h"
#include "Renderer.h"
#include <vector>

class Model
{
protected:
	Model(Geometry* T) : T(T) , mTransform(Matrix4::identity()){};
	void virtual draw(Renderer& r) = 0;
	Geometry* T;
	Matrix4 mTransform;
public:
	virtual ~Model() { delete T; T = nullptr; };
	void virtual print() = 0;
	//std::vector<ObjectGC*> m_Objects;
	//void addObj(IPObjectStruct* obj, double color[3]);
	//void print();
};

#endif