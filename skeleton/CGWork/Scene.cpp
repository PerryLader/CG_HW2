#include "Scene.h"
#include "ScreenCommand.h"

// Constructor
Scene::Scene():m_renderer(new Renderer()) {
    Camera* cam = new Camera();
    m_cameras.push_back(cam);
    m_primaryCameraIndex = 0;
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
void Scene::render(int width, int height, RenderMode& renderMode, ColorGC bg_color, ColorGC normalColor, ColorGC bBoxColor) const {
    m_renderer->render(m_cameras[0], width, height, m_models, renderMode, bg_color, normalColor,bBoxColor);//default camera
}
uint32_t* Scene::getBuffer() {
    return m_renderer->getBuffer();
}

void Scene::executeCommand(ScreenCommand* command) {
    command->execute(*this);
}

static float calculateTransformationMagnitude(const Vector3& ref_point,
    const Vector3& movement,
    float aspectRatio,
    float sensitivity,
    int width,
    int height) {
    return ((movement - ref_point).x / (width / aspectRatio) + (movement - ref_point).y / height) * sensitivity;
}

void Scene::applyToObjectSpace(const Matrix4& tMat) {
    for (Model* mod : m_models) {
        mod->modifiyTransformation(tMat);
    }
}
void Scene::applyToCamera(const Matrix4& tMat) {
    m_cameras[m_primaryCameraIndex]->translate(tMat);
}

void Scene::handleTransformationAction(const Vector3& ref_point,
    const Vector3& movement,
    float aspectRatio,
    int action,
    int axis,
    float sensitivity,
    int tSpace,
    int width,
    int height) {
    const float magnitude = calculateTransformationMagnitude(ref_point, movement, aspectRatio, sensitivity, width, height);
    Vector3 axisVector;
    Matrix4 Trasformation;
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
    default:
        axisVector = Vector3::unitX();
    }
    switch (action) {
    case ID_ACTION_ROTATE:
        Trasformation = Matrix4::rotation(magnitude, axis);
        break;
    case ID_ACTION_SCALE:
        Trasformation = Matrix4::scaling(Vector3::one() + axisVector * magnitude);
        break;
    case ID_ACTION_TRANSLATE:
        Trasformation = Matrix4::translate(axisVector* magnitude);
        break;
    default:
        Trasformation = Matrix4::rotation(magnitude, axis);
    }
    tSpace == ID_OBJECT_SPACE ? applyToObjectSpace(Trasformation) : applyToCamera(Trasformation); // should be a comparison between tSpace and some definition of what is ObjectSpace
}

void Scene::print() const {
    std::cout << "Scene:" << std::endl;
    for (const auto& elem : m_models)
        elem->print();
}