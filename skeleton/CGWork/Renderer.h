#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include "Model.h"
#include "Camera.h"
#include "Shader.h"
#include <iomanip>


#define RENDER_SHAPE                        1ULL<<1
#define RENDER_POLYGONS_CALC_NORMALS        1ULL<<2
#define RENDER_POLYGONS_NORMALS_FROM_DATA   1ULL<<3
#define RENDER_VETICES_NORMALS              1ULL<<4
#define RENDER_OBJ_BBOX                     1ULL<<5
#define RENDER_POLYGONS_BBOX                1ULL<<6


class RenderMode {
private:
    uint32_t flags = 1;
public:
    bool getRenderShape() { return RENDER_SHAPE & flags; }
    bool getRenderPolygonsCalcNormal() { return RENDER_POLYGONS_CALC_NORMALS & flags; }
    bool getRenderPolygonsNormalFromData() { return RENDER_POLYGONS_NORMALS_FROM_DATA & flags; }

    bool getRenderVertivesNormal() { return RENDER_VETICES_NORMALS & flags; }
    bool getRenderObjBbox() { return RENDER_OBJ_BBOX & flags; }
    bool getRenderPolygonsBbox() { return RENDER_POLYGONS_BBOX & flags; }
    
    bool setRenderShape() { flags&= RENDER_SHAPE & flags; }
    bool setRenderPolygonsCalcNormal() { flags &= RENDER_POLYGONS_CALC_NORMALS & flags; }
    bool setRenderPolygonsNormalFromData() { flags &= RENDER_POLYGONS_NORMALS_FROM_DATA & flags; }
    bool setRenderVertivesNormal() { flags &= RENDER_VETICES_NORMALS & flags; }
    bool setRenderObjBbox() { flags &= RENDER_OBJ_BBOX & flags; }
    bool setRenderPolygonsBbox() { flags &= RENDER_POLYGONS_BBOX & flags; }
    void unSetAll() { flags = 0; }

};
//enum RenderMode {
//    RENDER_ONLY_SHAPES,
//    RENDER_WITH_CALC_NORMALS,
//    RENDER_WITH_NORMALS
//    RENDER_WITH_BBOX
//    RENDER_WITH...
//};

class Renderer
{
public:
    Renderer();
    ~Renderer();
   // void addModel(Model* model);
    uint32_t* getBuffer() const;
    void render(const Camera* camera, int width, int height, const std::vector<Model*> models, RenderMode renderMode,
        const ColorGC& bgColor, const ColorGC& normalColor, const ColorGC& bBoxColor);

    void clear(bool clearBgBuffer);

private:
    uint32_t* m_Buffer; // RGB by width by height;
    float* m_ZBuffer; // width by height;
    uint32_t* m_BgBuffer; // width by height;
    Shader* m_shader;
    ColorGC m_bgColor;
    int m_width, m_height;

    void setWidth(int width) { m_width = width;};
    void setHeight(int height) { m_height = height;};
    void setBgColor(const ColorGC& bgColor) { m_bgColor = bgColor;};

    int getWidth() const { return m_width; };
    int getHeight() const { return m_height; };
    ColorGC getBgColor() const { return m_bgColor; };

    void createBuffers();
    void refreshBgBuffer();
    void Renderer::createPolyNormalLlinesFromData(std::vector<Geometry*> transformedGeometries, std::vector<Line>& edges, const ColorGC& bBoxColor);
    void Renderer::createPolyCalcNormalLlines(std::vector<Geometry*> transformedGeometries, std::vector<Line>& edges, const ColorGC& bBoxColor);
    void createShapesLines(std::vector<Geometry*> transformedGeometries, std::vector<Line>& edges);
    void createObjBboxLines(std::vector<Geometry*> transformedGeometries, std::vector<Line>& edges, const ColorGC& bBoxColor);
    void createPolyBboxLines(std::vector<Geometry*> transformedGeometries,  std::vector<Line>& edges, const ColorGC& bBoxColor);
    
};

#endif // RENDERER_H


