#include "Scene.h"

// Constructor
Scene::Scene() : transformation(Matrix4::identity()) {}

// Function to add a model to the scene
void Scene::addModel(const Model& model) {
    models.push_back(model);
    for (const auto& polygon : model.polygons) {
        renderer.addPolygon(polygon);
    }
}

// Function to add a camera to the scene
void Scene::addCamera(const Camera& camera) {
    cameras.push_back(camera);
}

// Function to set the transformation matrix
void Scene::setTransformation(const Matrix4& transformation) {
    this->transformation = transformation;
    renderer.setTransformation(transformation);
}

// Function to render the scene
void Scene::render() const {
    renderer.render();
}
