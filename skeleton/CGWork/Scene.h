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
    void addModel(const Model& model);

    // Function to add a camera to the scene
    void addCamera(const Camera& camera);

    // Function to set the transformation matrix
    void setTransformation(const Matrix4& transformation);

    // Function to render the scene
    void render() const;

private:
    std::vector<Model> models;
    std::vector<Camera> cameras;
    Renderer renderer;
    Matrix4 transformation;
};

#endif // SCENE_H
