#include "Scene.h"
#include "ICommand.h"

// Constructor
Scene::Scene():m_renderer(new Renderer()) {
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
void Scene::render(int width, int height, RenderMode renderMode, ColorGC bg_color, ColorGC normalColor, ColorGC bBoxColor) const {
    m_renderer->render(m_cameras[0], width, height, m_models, renderMode, bg_color, normalColor,bBoxColor);//default camera
}
uint32_t* Scene::getBuffer() {
    return m_renderer->getBuffer();
}

void Scene::executeCommand(ICommand* command) {
    command->execute(*this);
}

void Scene::handleTransformationAction(const Vector3& ref_point,
    const Vector3& movement,
    float aspectRatio,
    int action,
    int axis,
    float sensitivity,
    int tSpace) {
    Vector3 axisVector = Vector3::unitX();
    switch(axis){
    case ID_AXIS_X:
        axisVector = Vector3::unitX();
        break;
    case ID_AXIS_Y:
        axisVector = Vector3::unitY();
        break;
    case ID_AXIS_Z:
        axisVector = Vector3::unitZ();
        break;
    }
    Matrix4 Trasformation = Matrix4::identity();
    float magnitude = Vector3::dot((movement - ref_point), axisVector) * sensitivity;
    switch (action) {
    case ID_ACTION_ROTATE:
        switch (axis) {
        case ID_AXIS_X:
            Trasformation = Matrix4::rotationX(magnitude);
            break;
        case ID_AXIS_Y:
            Trasformation = Matrix4::rotationY(magnitude);
            break;
        case ID_AXIS_Z:
            Trasformation = Matrix4::rotationZ(magnitude);
            break;
        }
        break;
    case ID_ACTION_SCALE:
        Trasformation = Matrix4::scaling(Vector3::one()*magnitude);
        break;
    case ID_ACTION_TRANSLATE:
        Trasformation = Matrix4::translate((movement - ref_point) * sensitivity);
        break;
    }
    bool ObjecetSpace = tSpace; // should be a comparison between tSpace and some definition of what is ObjectSpace
    if (ObjecetSpace) {
        for (Model* mod : m_models) {
            mod->modifiyTransformation(Trasformation);
        }
    }
    else {
        m_cameras[0]->modifiyView(Trasformation);
    }
}
void Scene::print() const {
    std::cout << "Scene:" << std::endl;
    for (const auto& elem : m_models)
        elem->print();
}