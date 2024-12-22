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
const uint32_t RENDER_OVERRIDER_BACKGROUND_COLOR = 256;


class RenderMode {
private:
	uint32_t flags =1;
public:
	bool getRenderShape() { return RENDER_SHAPE & flags; }
	bool getRenderPolygonsCalcNormal() { return RENDER_POLYGONS_CALC_NORMALS & flags; }
	bool getRenderPolygonsNormalFromData() { return RENDER_POLYGONS_NORMALS_FROM_DATA & flags; }
	bool getRenderCalcVertivesNormal() { return RENDER_CALC_VETICES_NORMALS & flags; }
	bool getRenderDataVertivesNormal() { return RENDER_DATA_VETICES_NORMALS & flags; }
	bool getRenderObjBbox() { return RENDER_OBJ_BBOX & flags; }
	bool getRenderPolygonsBbox() { return RENDER_POLYGONS_BBOX & flags; }
	bool getRenderOverrideWireColor() { return RENDER_OVERRIDER_WIRE_COLOR & flags; }
	bool getRenderOverrideBackgroundColor() { return RENDER_OVERRIDER_BACKGROUND_COLOR & flags; }

	void setRenderShape() { flags ^= RENDER_SHAPE; }
	void setRenderPolygonsCalcNormal() { flags ^= RENDER_POLYGONS_CALC_NORMALS; }
	void setRenderPolygonsNormalFromData() { flags ^= RENDER_POLYGONS_NORMALS_FROM_DATA; }
	void setRenderCalcVertivesNormal() { flags ^= RENDER_CALC_VETICES_NORMALS; }
	void setRenderDataVertivesNormal() { flags ^= RENDER_DATA_VETICES_NORMALS; }
	void setRenderObjBbox() { flags ^= RENDER_OBJ_BBOX; }
	void setRenderPolygonsBbox() { flags ^= RENDER_POLYGONS_BBOX; }
	void setRenderOverrideWireColor() { flags ^= RENDER_OVERRIDER_WIRE_COLOR; }
	void setRenderOverrideBackgroundColor() { flags ^= RENDER_OVERRIDER_BACKGROUND_COLOR;}

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
	

	std::vector<Line>* getEdges() const;
	std::vector<Line> getPolyBboxLines(const ColorGC& bBoxColor);
	std::vector<Line> getPolyNormalLineFromData(const ColorGC& normalColor);
	std::vector<Line> calcPolyNormalLine(const ColorGC& normalColor);
	void createShapesLines(std::vector<Line> lines[LineVectorIndex::LAST]);
	void createObjBboxLines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC& bBoxColor);
	void createPolyBboxLines(std::vector<Line> lines[LineVectorIndex::LAST],const ColorGC& bBoxColor);
	void createPolyNormalLlinesFromData(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC& bBoxColor);
	void createPolyCalcNormalLlines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC& bBoxColor);
	void createVertCalcNormalLlines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC& bBoxColor);
	void createVertDataNormalLlines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC& bBoxColor);
	//void calVertexNormal();

public:
	std::unordered_map<Vector3, std::shared_ptr<Vertex>, KeyHash, KeyEqual> m_map;

	std::string getName();
	Geometry(std::string name);
	Geometry::Geometry(std::string name, std::unordered_map<Vector3, std::shared_ptr<Vertex>, KeyHash, KeyEqual> map);
	BBox getBBox() const;
	
	
	void loadLines(std::vector<Line> lines[LineVectorIndex::LAST],const ColorGC& bBoxColor, const ColorGC& normalColor, RenderMode renderMode);
	void Geometry::addPolygon(PolygonGC* poli);
	Geometry* applyTransformation(const Matrix4& tMat) const;
	
	void backFaceCulling();
	void clip();
	void print() const;
	~Geometry();
};

#endif