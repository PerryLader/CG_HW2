#include "Scene.h"

// Constructor
Scene::Scene() {}

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

// Function to render the scene
void Scene::render() const {
    m_renderer->render();
}

void Scene::print() const {
    std::cout << "Scene:" << std::endl;
    for (const auto& elem : m_models)
        elem->print();
}