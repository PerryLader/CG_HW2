#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Model.h"
#include "Camera.h"
#include "Renderer.h"

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
    void render() const;

    void print() const;

private:
    std::vector<Model*> m_models;
    std::vector<Camera*> m_cameras;
    Renderer* m_renderer;
};

#endif // SCENE_H
