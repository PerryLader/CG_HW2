#include "Geometry.h"

Geometry::Geometry(std::string name) : m_name(name) ,m_bBox(){}

Geometry::Geometry(std::string name, std::unordered_map<Vector3, std::shared_ptr<Vertex>, KeyHash, KeyEqual> map) : m_name(name), m_bBox(),m_map(map){}
// Destructor
Geometry::~Geometry() {
	for (PolygonGC* polygon : m_polygons) {
		delete polygon;
	}
	m_polygons.clear();
}

BBox Geometry::getBBox() const{
	return m_bBox;
}
std::string Geometry::getName() {
	return this->m_name;
}

void Geometry::addPolygon(PolygonGC* poli)
{
	this->m_polygons.push_back(poli);
	m_bBox.updateBBox(poli->getBbox());
}

Geometry* Geometry::applyTransformation(const Matrix4& tMat) const{
	for (std::pair<Vector3, std::shared_ptr<Vertex>> t : m_map)
	{
		t.second->setCalcNormal();		
	}
	Geometry* res = new Geometry(m_name,this->m_map);
	for (const auto& poly : m_polygons) {

		res->addPolygon(poly->applySoftTransformation(tMat));
	}
	return res;
}
std::vector<Line>* Geometry::getEdges(const ColorGC* overridingColor) const {
	
	std::vector<Line>* res = new std::vector<Line>;
	for (const auto& poly : m_polygons) {
		const std::vector<Line>* edges = poly->getEdges(overridingColor);
		res->insert(res->end(), edges->begin(), edges->end());
		delete edges;
	}
	return res;
}

void Geometry::backFaceCulling() {
    const Vector3 camera_vec = Vector3::unitZ();
	for (auto it = m_polygons.begin(); it != m_polygons.end(); ) {
		PolygonGC* polygon = *it;
		if (polygon->isBehindCamera() || Vector3::dot(camera_vec, polygon->getCalcNormal()) < 0) {
			delete polygon;
			it = m_polygons.erase(it);
		}
		else
			it++;
	}
}

std::vector<Line> Geometry::getPolyBboxLines(const ColorGC* overridingColor) const
{
	std::vector<Line> lines;
	for (auto t : m_polygons)
	{
		std::vector<Line> polyLines=t->getPolyBboxLine(overridingColor);
		lines.insert(lines.end(), polyLines.begin(), polyLines.end());
	}
	return lines;
}

std::vector<Line> Geometry::getPolyNormalLineFromCalc(const ColorGC* overridingColor) const
{
	std::vector<Line> lines;
	for (auto t : m_polygons)
	{
		lines.push_back(t->calcNormalLine(overridingColor));
	}
	return lines;
}



void Geometry::createShapesLines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC* overridingColor) const
{
	const std::vector<Line>* geomEdges = this->getEdges(overridingColor);
	lines[LineVectorIndex::SHAPES].insert(lines[LineVectorIndex::SHAPES].end(), geomEdges->begin(), geomEdges->end());
	delete geomEdges;

#ifdef APPLE_ALGO
	for (auto& edge : edges) {
		edge.computeQuantitativeVisibility(transformedGeometries);
	}
#endif // APPLE_ALGO

}
void Geometry::createObjBboxLines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC& wireColor) const
{
	std::vector<Line> bBoxLines = this->getBBox().getLinesOfBbox(wireColor);
	lines[LineVectorIndex::OBJ_BBOX].insert(lines[LineVectorIndex::OBJ_BBOX].end(), bBoxLines.begin(), bBoxLines.end());	
}
void Geometry::createPolyBboxLines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC* overridingColor) const
{
	
	std::vector<Line> bBoxLines = this->getPolyBboxLines(overridingColor);
	lines[LineVectorIndex::POLY_BBOX].insert(lines[LineVectorIndex::POLY_BBOX].end(), bBoxLines.begin(), bBoxLines.end());

}
void Geometry::createPolyNormalLlinesFromData(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC* overridingColor) const
{
	std::vector<Line> normalLines = this->getPolyNormalLineFromData(overridingColor);
	lines[LineVectorIndex::POLY_DATA_NORNAL].insert(lines[LineVectorIndex::POLY_DATA_NORNAL].end(), normalLines.begin(), normalLines.end());
	
}
void Geometry::createPolyCalcNormalLlines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC* overridingColor) const
{	
	std::vector<Line> normalLines = this->getPolyNormalLineFromCalc(overridingColor);
	lines[LineVectorIndex::POLY_CALC_NORNAL].insert(lines[LineVectorIndex::POLY_CALC_NORNAL].end(), normalLines.begin(), normalLines.end());
}
void Geometry::createVertCalcNormalLlines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC* overridingColor) const
{
	std::vector<Line> normalLines;
	for (auto poly : this->m_polygons)
	{
		for (auto vert : poly->getVertexVector())
		{
			Vector3 vec = vert->getCalcNormal();
			Vector3 centerPoint = vert->loc();
			normalLines.push_back(Line(centerPoint, centerPoint + (vec.normalized() * 0.25)));
		}
	}
	
	lines[LineVectorIndex::VERTICES_CALC_NORMAL].insert(lines[LineVectorIndex::VERTICES_CALC_NORMAL].end(), normalLines.begin(), normalLines.end());

}
void Geometry::createVertDataNormalLlines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC* overridingColor) const
{
	std::vector<Line> normalLines;
	for (auto poly : this->m_polygons)
	{
		for (auto vert : poly->getVertexVector())
		{
			Vector3 vec = vert->getDataNormal();
			Vector3 centerPoint = vert->loc();
			normalLines.push_back(Line(centerPoint, centerPoint + (vec.normalized() * 0.25)));
		}
	}

	lines[LineVectorIndex::VERTICES_DATA_NORMAL].insert(lines[LineVectorIndex::VERTICES_DATA_NORMAL].end(), normalLines.begin(), normalLines.end());

}



void Geometry::loadLines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC& wireColor, const ColorGC& normalColor, RenderMode renderMode)
{
	if (renderMode.getRenderShape())
	{
		this->createShapesLines(lines , renderMode.getRenderOverrideWireColor() ? &wireColor : nullptr);
	}
	if (renderMode.getRenderObjBbox())
	{
		this->createObjBboxLines(lines, renderMode.getRenderOverrideWireColor() ? wireColor : ColorGC::defaultColor());
	}
	if (renderMode.getRenderPolygonsBbox())
	{
		this->createPolyBboxLines(lines, renderMode.getRenderOverrideWireColor() ? &wireColor : nullptr);
	}
	if (renderMode.getRenderPolygonsCalcNormal())
	{
		this->createPolyCalcNormalLlines(lines, renderMode.getRenderOverrideNormalColor() ? &normalColor : nullptr);
	}
	if (renderMode.getRenderPolygonsNormalFromData())
	{
		this->createPolyNormalLlinesFromData(lines, renderMode.getRenderOverrideNormalColor() ? &normalColor : nullptr);
	}
	if (renderMode.getRenderCalcVertivesNormal())
	{
		this->createVertCalcNormalLlines(lines, renderMode.getRenderOverrideNormalColor() ? &normalColor : nullptr);
	}
	if (renderMode.getRenderDataVertivesNormal())
	{
		
		this->createVertDataNormalLlines(lines, renderMode.getRenderOverrideNormalColor() ? &normalColor : nullptr);
		
	}
}

std::vector<Line> Geometry::getPolyNormalLineFromData(const ColorGC* overridingColor) const
{
	std::vector<Line> lines;
	for (auto t : m_polygons)
	{
		lines.push_back( t->getNormalLineFromData(overridingColor));
	}
	return lines;
}

void Geometry::clip() {
	//m_bBox.c
	for (PolygonGC* temp : m_polygons)
		temp->clip();
}

void Geometry::print() const
{
	int i = 0;
	for (const PolygonGC* temp : m_polygons)
	{
		std::cout << "		Polygon[" << i << "] vertices:" << std::endl;
		temp->printVertices();
		i++;
	}
}