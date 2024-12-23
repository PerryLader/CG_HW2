#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Model.h"
#include "Camera.h"
#include "Renderer.h"
#include "resource.h"

class ScreenCommand;

class Scene {
public:
    
    // Constructor
    Scene();

    // Function to add a model to the scene
    void addModel(Model* model);

    void addModels(const std::vector<Model*>& models);
    // Function to add a camera to the scene
    void addCamera(Camera* camera);
    // Function to render the scene
    void render(int width, int height, RenderMode& renderMode, ColorGC bg_color, ColorGC normalColor, ColorGC bBoxColor) const;
    uint32_t* getBuffer();
    void executeCommand(ScreenCommand* command);

    void applyToObjectSpace(const Matrix4& tMat);
    void applyToCamera(const Matrix4& tMat);
    void setCamera(CAMERA_TYPE cameraType);
    Camera* getPerspectiveCamera();
    void handleTransformationAction(const Vector3& ref_point,
         const Vector3& movement,
         float aspectRatio,
         int action,
         int axis,
         float sensitivity,
         int tSpace,
        int width,
        int height);

    void print() const;

private:
    std::vector<Model*> m_models;
    std::vector<Camera*> m_cameras;
    Renderer* m_renderer;
    int m_primaryCameraIndex;
};

#endif // SCENE_H
