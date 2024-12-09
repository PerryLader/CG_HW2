#include "Scene.h"

// Constructor
Scene::Scene() : m_transformation(Matrix4::identity()) {}

// Function to add a model to the scene
void Scene::addModel(Model* model) {
    m_models.push_back(model);
}

void Scene::addModels(const std::vector<Model*>& models) {
    m_models.insert(m_models.end(), models.begin(), models.end());
}

// Function to add a camera to the scene
void Scene::addCamera(Camera* camera) {
    m_cameras.push_back(camera);
}

// Function to set the transformation matrix
void Scene::setTransformation(const Matrix4& transformation) {
    this->m_transformation = transformation;
}

// Function to render the scene
void Scene::render() const {
}


void Scene::print() const {
    std::cout << "Scene:" << std::endl;
    for (const auto& elem : m_models)
        elem->print();
}