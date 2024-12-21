#ifndef	GEOMETRY_H
#define	GEOMETRY_H
#include "Polygon.h"
#include <vector>
#include <string>


#define RENDER_SHAPE                        1ULL
#define RENDER_POLYGONS_CALC_NORMALS        1ULL<<1
#define RENDER_POLYGONS_NORMALS_FROM_DATA   1ULL<<2
#define RENDER_VETICES_NORMALS              1ULL<<3
#define RENDER_OBJ_BBOX                     1ULL<<4
#define RENDER_POLYGONS_BBOX                1ULL<<5


class RenderMode {
private:
	uint32_t flags =3;
public:
	bool getRenderShape() { return RENDER_SHAPE & flags; }
	bool getRenderPolygonsCalcNormal() { return RENDER_POLYGONS_CALC_NORMALS & flags; }
	bool getRenderPolygonsNormalFromData() { return RENDER_POLYGONS_NORMALS_FROM_DATA & flags; }

	bool getRenderVertivesNormal() { return RENDER_VETICES_NORMALS & flags; }
	bool getRenderObjBbox() { return RENDER_OBJ_BBOX & flags; }
	bool getRenderPolygonsBbox() { return RENDER_POLYGONS_BBOX & flags; }

	bool setRenderShape() { flags &= RENDER_SHAPE & flags; }
	bool setRenderPolygonsCalcNormal() { flags &= RENDER_POLYGONS_CALC_NORMALS & flags; }
	bool setRenderPolygonsNormalFromData() { flags &= RENDER_POLYGONS_NORMALS_FROM_DATA & flags; }
	bool setRenderVertivesNormal() { flags &= RENDER_VETICES_NORMALS & flags; }
	bool setRenderObjBbox() { flags &= RENDER_OBJ_BBOX & flags; }
	bool setRenderPolygonsBbox() { flags &= RENDER_POLYGONS_BBOX & flags; }
	void unSetAll() { flags = 0; }

};
enum LineVectorIndex{
SHAPES=0,
POLY_CALC_NORNAL=1,
POLY_DATA_NORNAL=2,
VERTICES_NORMAL=2,
OBJ_BBOX=4,
POLY_BBOX=5,
LAST=6
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


public:
	std::string getName();
	Geometry(std::string name);
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