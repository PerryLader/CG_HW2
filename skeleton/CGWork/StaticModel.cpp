#include "StaticModel.h"
#include <iostream>

// Constructor
StaticModel::StaticModel(const Geometry& T) : Model(T){
    // Initialization code if needed
}

// Destructor
StaticModel::~StaticModel() {
    // Cleanup code if needed
}

void StaticModel::draw(Renderer& r) {
    Geometry transfromedGeometry = T.applyTransformation(mTransform);
    r.addModel(transfromedGeometry);
}

// Override the print function
void StaticModel::print() {
    // Implement the print logic for the static model
    std::cout << "StaticModel:" << std::endl;
    // Example: Print the transformation matrix and geometry
    mTransform.print();
    T.print();
}
