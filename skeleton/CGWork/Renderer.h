#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include "Model.h"
#include "Camera.h"
#include "Shader.h"

class Renderer
{
public:
    Renderer(int width, int height);
    ~Renderer();
    void addModel(const Model* model);
    void render(const Camera* camera, int width, int height);
    void clear();

private:
    float* m_Buffer; // RGB by width by height;
    float* m_ZBuffer; // width by height;
    Shader* shader;
    std::vector<const Model*> m_models_to_render;
    void createBuffers(int width, int height);
};

#endif // RENDERER_H


