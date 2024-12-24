#include "Scene.h"
#include "ScreenCommand.h"

// Constructor
Scene::Scene():m_renderer(new Renderer()) {
    Camera* camOrtho = new Camera();   
    camOrtho->setOrthogonal(Vector3(-1, 1, 1), Vector3(1, -1, 5), 0, 0);
    m_cameras.push_back(camOrtho);

    Camera* camPrespective = new Camera();
    camPrespective->setPerspective(45, 1, 1, 5);
    m_cameras.push_back(camPrespective);

    m_primaryCameraIndex = CAMERA_TYPE::ORTHOGONAL;
}
// Function to add a model to the scene
void Scene::addModel(Model* model) {
    m_models.push_back(model);
}

void Scene::addModels(const std::vector<Model*>& models) {
    
    
    BBox sceneBbox(Vector3(FLT_MAX, FLT_MAX, FLT_MAX), Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX));

    for (auto& m : models)
    {

        sceneBbox.updateBBox(m->getGeormetryBbox());
    }

    Vector3 max = sceneBbox.getMax();
    Vector3 min = sceneBbox.getMin();
    //scale
    //scale the scene into 2,-2 cube
    float scaleFactor = 1 / (std::max(max.x - min.x, std::max(max.y - min.y, max.z - min.z))/2);
    Matrix4 scaleMatrix= Matrix4::scaling(Vector3(scaleFactor, scaleFactor, scaleFactor));

    //centerized
    Vector3 oldCenter = (max + min) * 0.5;
    Vector3 diff = -oldCenter;
    Matrix4 trans = Matrix4::translate(diff);
    for (auto& m : models)
    {        
        m->modifiyTransformation(trans);
        m->modifiyTransformation(scaleMatrix);
    }
    m_models.insert(m_models.end(), models.begin(), models.end());
}

// Function to add a camera to the scene
void Scene::addCamera(Camera* camera) {
    
    m_cameras.push_back(camera);
}

// Function to render the scene
void Scene::render(int width, int height, RenderMode& renderMode, ColorGC bg_color, ColorGC normalColor, ColorGC bBoxColor) const {
    m_renderer->render(m_cameras[m_primaryCameraIndex], width, height, m_models, renderMode, bg_color, normalColor,bBoxColor);//default camera
}
uint32_t* Scene::getBuffer() {
    return m_renderer->getBuffer();
}

void Scene::executeCommand(ScreenCommand* command) {
    command->execute(*this);
}

static void calculateTransformationMagnitude(float& X_mag, float& Y_mag,  const Vector3& ref_point,
    const Vector3& movement,
    float aspectRatio,
    float sensitivity,
    int width,
    int height) {
    X_mag = ((movement - ref_point).x / (width / aspectRatio)) * sensitivity;
    Y_mag = ((movement - ref_point).y / (height / aspectRatio)) * sensitivity;
}

void Scene::applyToObjectSpace(const Matrix4& tMat) {
    for (Model* mod : m_models) {
        mod->modifiyTransformation(tMat);
    }
}
void Scene::applyToCamera(const Matrix4& tMat) {
    for (auto& c : m_cameras)
    {
        c->translate(tMat);
    }
}

void Scene::setCamera(CAMERA_TYPE cameraType)
{
    this->m_primaryCameraIndex = cameraType;
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
    float X_mag, Y_mag; 
    calculateTransformationMagnitude(X_mag, Y_mag,ref_point, movement, aspectRatio, sensitivity, width, height);
    Vector3 axisVector;
    Matrix4 invTrasformation;
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
    case ID_AXIS_XY:
        axisVector = Vector3::unitX() + Vector3::unitY();
        break;
    case ID_AXIS_XYZ:
        axisVector = Vector3::one();
        break;
    default:
        axisVector = Vector3::unitX();
    }
    switch (action) {
    case ID_ACTION_ROTATE:
        invTrasformation = Matrix4::rotation(X_mag+Y_mag, axis).inverse();
        break;
    case ID_ACTION_SCALE:
        invTrasformation = Matrix4::scaling(Vector3::one() + axisVector * (X_mag + Y_mag)).inverse();
        break;
    case ID_ACTION_TRANSLATE:
        invTrasformation = Matrix4::translate(axisVector.scale(X_mag, Y_mag, 0)).inverse();
        break;
    default:
        invTrasformation = Matrix4::rotation(X_mag + Y_mag, axis).inverse();
    }
    tSpace == ID_OBJECT_SPACE ? applyToObjectSpace(invTrasformation) : applyToCamera(invTrasformation); // should be a comparison between tSpace and some definition of what is ObjectSpace
}

void Scene::print() const {
    std::cout << "Scene:" << std::endl;
    for (const auto& elem : m_models)
        elem->print();
}