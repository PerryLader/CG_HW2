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
    Renderer();
    ~Renderer();
   // void addModel(Model* model);
    float* getBuffer();
    void render(const Camera* camera, int width, int height,const std::vector<Model*> m_models, const ColorGC& bgColor);
    void clear();

private:
    float* m_Buffer; // RGB by width by height;
    float* m_ZBuffer; // width by height;
    Shader* m_shader;
  //  std::vector<Model*> m_models_to_render;
    void createBuffers(const ColorGC& bg_color,int width, int height);
   // void fillBackgroundColor(const ColorGC& bg_color);
};

#endif // RENDERER_H


