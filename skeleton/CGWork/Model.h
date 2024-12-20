#ifndef	MODEL_H
#define	MODEL_H

#include "Geometry.h"
//#include "Renderer.h"
#include <vector>

class Model
{
protected:
	Model(Geometry* T) : T(T) , mTransform(Matrix4::identity()){};
	void virtual draw(/*Renderer& r*/) = 0;
	Geometry* T;
	Matrix4 mTransform;
public:
	virtual ~Model() { delete T; T = nullptr; };

	Geometry* onDraw(const Matrix4 viewProjectionMatrix)
	{
		return T->applyTransformation(mTransform* viewProjectionMatrix);
	}
	
	void modifiyTransformation(const Matrix4& tMat){
		mTransform = mTransform*tMat;
	}
	
	void virtual print() = 0;
};

#endif