#ifndef	GEOMETRY_H
#define	GEOMETRY_H
#include "Polygon.h"
#include <vector>
#include <string>
#include <unordered_map>

const uint32_t RENDER_SHAPE = 1;
const uint32_t RENDER_POLYGONS_CALC_NORMALS = 2;
const uint32_t RENDER_POLYGONS_NORMALS_FROM_DATA = 4;
const uint32_t RENDER_CALC_VETICES_NORMALS = 8;
const uint32_t RENDER_DATA_VETICES_NORMALS = 16;
const uint32_t RENDER_OBJ_BBOX = 32;
const uint32_t RENDER_POLYGONS_BBOX = 64;
const uint32_t RENDER_OVERRIDER_WIRE_COLOR = 128;
const uint32_t RENDER_OVERRIDER_NORMAL_COLOR = 256;


class RenderMode {
private:
	uint32_t flags =1;
public:
	bool getRenderShape() const { return RENDER_SHAPE & flags; }
	bool getRenderPolygonsCalcNormal() const { return RENDER_POLYGONS_CALC_NORMALS & flags; }
	bool getRenderPolygonsNormalFromData() const { return RENDER_POLYGONS_NORMALS_FROM_DATA & flags; }
	bool getRenderCalcVertivesNormal() const { return RENDER_CALC_VETICES_NORMALS & flags; } 
	bool getRenderDataVertivesNormal() const { return RENDER_DATA_VETICES_NORMALS & flags; } 
	bool getRenderObjBbox() const { return RENDER_OBJ_BBOX & flags; } 
	bool getRenderPolygonsBbox()  const { return RENDER_POLYGONS_BBOX & flags; } 
	bool getRenderOverrideWireColor() const { return RENDER_OVERRIDER_WIRE_COLOR & flags; } 
	bool getRenderOverrideNormalColor() const { return RENDER_OVERRIDER_NORMAL_COLOR & flags; } 

	void setRenderShape() { flags ^= RENDER_SHAPE; }
	void setRenderPolygonsCalcNormal() { flags ^= RENDER_POLYGONS_CALC_NORMALS; }
	void setRenderPolygonsNormalFromData() { flags ^= RENDER_POLYGONS_NORMALS_FROM_DATA; }
	void setRenderCalcVertivesNormal() { flags ^= RENDER_CALC_VETICES_NORMALS; }
	void setRenderDataVertivesNormal() { flags ^= RENDER_DATA_VETICES_NORMALS; }
	void setRenderObjBbox() { flags ^= RENDER_OBJ_BBOX; }
	void setRenderPolygonsBbox() { flags ^= RENDER_POLYGONS_BBOX; }
	void setRenderOverrideWireColor() { flags ^= RENDER_OVERRIDER_WIRE_COLOR; }
	void setRenderOverrideNormalColor() { flags ^= RENDER_OVERRIDER_NORMAL_COLOR;}

	void unSetAll() { flags = 0; }

};
enum LineVectorIndex{
SHAPES=0,
POLY_CALC_NORNAL=1,
POLY_DATA_NORNAL=2,
VERTICES_CALC_NORMAL=3,
VERTICES_DATA_NORMAL = 4,
OBJ_BBOX=5,
POLY_BBOX=6,
LAST=7
};
struct KeyHash {
	std::size_t operator()(const Vector3 key) const {

		std::hash<float> hasher;
		return hasher(key.x) ^ (hasher(key.y) << 1) ^ (hasher(key.z) << 2);
	}
};
struct KeyEqual {
	bool operator()(const Vector3& lhs,
		const Vector3& rhs) const {
		return lhs == rhs;
	}
};

class Geometry
{
private:
	std::vector<PolygonGC*> m_polygons;
	std::string m_name;
	BBox m_bBox;
	ColorGC m_objColor;

	std::vector<Line>* getEdges(const ColorGC* overridingColor) const;
	std::vector<Line> getPolyBboxLines(const ColorGC* overridingColor) const;
	std::vector<Line> getPolyNormalLineFromData(const ColorGC* overridingColor) const;
	std::vector<Line> getPolyNormalLineFromCalc(const ColorGC* overridingColor) const;
	void createShapesLines(std::vector<Line> lines[LineVectorIndex::LAST],const ColorGC* overridingColor) const;
	void createObjBboxLines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC* wireColor) const;
	void createPolyBboxLines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC* overridingColor) const;
	void createPolyNormalLlinesFromData(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC* overridingColor) const;
	void createPolyCalcNormalLlines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC* overridingColor) const;
	void createVertCalcNormalLlines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC* overridingColor) const;
	void createVertDataNormalLlines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC* overridingColor) const;
	//void calVertexNormal();

public:
	std::unordered_map<Vector3, std::shared_ptr<Vertex>, KeyHash, KeyEqual> m_map;

	std::string getName() const;
	Geometry(const std::string& name, const ColorGC& color);
	BBox getBBox() const;
	
	void loadLines(std::vector<Line> lines[LineVectorIndex::LAST],const ColorGC& bBoxColor, const ColorGC& normalColor, RenderMode& renderMode) const;
	void Geometry::addPolygon(PolygonGC* poli);
	Geometry* applyTransformation(const Matrix4& tMat) const;
	void calcVertxNormal();
	void backFaceCulling();
	void clip();
	bool isClippedByBBox(const Matrix4& tMat) const;
	void print() const;
	~Geometry();
};

#endif