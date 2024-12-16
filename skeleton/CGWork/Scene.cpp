#include "Scene.h"

// Constructor
Scene::Scene() {
    Camera* cam = new Camera();
    m_cameras.push_back(cam);

}

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
void Scene::render(int width, int height) const {
    m_renderer->render(m_cameras[0], width, height);//default camera
}
float* Scene::getBuffer() {
    return m_renderer->getBuffer();
}

void Scene::print() const {
    std::cout << "Scene:" << std::endl;
    for (const auto& elem : m_models)
        elem->print();
}