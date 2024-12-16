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
	Matrix4 getModelTransformation() const{
		return mTransform;
	}
	void modifiyTransformation(const Matrix4& tMat){
		mTransform = mTransform*tMat;
	}
	Geometry* applyTransformation(const Matrix4& mTransform) const {
		return T->applyTransformation(mTransform);
	}
	void virtual print() = 0;
};

#endif