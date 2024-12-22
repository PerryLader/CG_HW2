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
	//for (PolygonGC* poly : m_polygons) {
	//	//std::pair<PolygonGC*, std::vector<Vertex*>> t(poly, poly->getVertexVector());
	//	std::vector <Vertex*> vertexVector = poly->getVertexVector();
	//	for (Vertex* vertex : vertexVector)
	//	{
	//		m_map[vertex->loc()].push_back(std::pair<PolygonGC*, Vertex*>(poly, vertex));
	//	}
	//}
	//	
	//	
	//for (std::pair<Vector3,std::vector<std::pair<PolygonGC*, Vertex*>>> pair : map)
	//{
	//	std::vector<std::pair<PolygonGC*, Vertex*>> vec = pair.second;
	//	Vector3 avrageNormal(0, 0, 0);
	//	for (std::pair<PolygonGC*, Vertex*> t : vec)
	//	{
	//		avrageNormal= avrageNormal + t.first->getCalcNormal();
	//	}
	//	avrageNormal = avrageNormal * (1 / vec.size());
	//	for (std::pair<PolygonGC*, Vertex*> t : vec)
	//	{
	//		t.second->setDataNormal(avrageNormal);
	//	}
	//}

}

Geometry* Geometry::applyTransformation(const Matrix4& tMat) const{
	for (std::pair<Vector3, std::shared_ptr<Vertex>> t : m_map)
	{
		t.second->transformVertex(tMat);
		t.second->m_hasTranformed = true;
	}
	Geometry* res = new Geometry(m_name,this->m_map);
	for (const auto& poly : m_polygons) {

		res->addPolygon(poly->applySoftTransformation(tMat));
	}
	return res;
}
std::vector<Line>* Geometry::getEdges() const {
	
	
	std::vector<Line>* res = new std::vector<Line>;
	for (const auto& poly : m_polygons) {
		const std::vector<Line>* edges = poly->getEdges();
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

std::vector<Line> Geometry::getPolyBboxLines(const ColorGC& bBoxColor)
{
	std::vector<Line> lines;
	for (auto t : m_polygons)
	{
		std::vector<Line> polyLines=t->getPolyBboxLine(bBoxColor);
		lines.insert(lines.end(), polyLines.begin(), polyLines.end());
	}
	return lines;
}

std::vector<Line> Geometry::calcPolyNormalLine(const ColorGC& normalColor)
{
	std::vector<Line> lines;
	for (auto t : m_polygons)
	{
		lines.push_back(t->calcNormalLine(normalColor));
	}
	return lines;
}



void Geometry::createShapesLines(std::vector<Line> lines[LineVectorIndex::LAST])
{
	const std::vector<Line>* geomEdges = this->getEdges();
	lines[LineVectorIndex::SHAPES].insert(lines[LineVectorIndex::SHAPES].end(), geomEdges->begin(), geomEdges->end());
	

#ifdef APPLE_ALGO
	for (auto& edge : edges) {
		edge.computeQuantitativeVisibility(transformedGeometries);
	}
#endif // APPLE_ALGO

}
void Geometry::createObjBboxLines(std::vector<Line> lines[LineVectorIndex::LAST],  const ColorGC& bBoxColor)
{
	std::vector<Line> bBoxLines = this->getBBox().getLinesOfBbox(bBoxColor);
	lines[LineVectorIndex::OBJ_BBOX].insert(lines[LineVectorIndex::OBJ_BBOX].end(), bBoxLines.begin(), bBoxLines.end());	
}
void Geometry::createPolyBboxLines(std::vector<Line> lines[LineVectorIndex::LAST],  const ColorGC& bBoxColor)
{
	
	std::vector<Line> bBoxLines = this->getPolyBboxLines(bBoxColor);
	lines[LineVectorIndex::POLY_BBOX].insert(lines[LineVectorIndex::POLY_BBOX].end(), bBoxLines.begin(), bBoxLines.end());

}
void Geometry::createPolyNormalLlinesFromData(std::vector<Line> lines[LineVectorIndex::LAST],  const ColorGC& normalColor)
{
	std::vector<Line> normalLines = this->getPolyNormalLineFromData(normalColor);
	lines[LineVectorIndex::POLY_DATA_NORNAL].insert(lines[LineVectorIndex::POLY_DATA_NORNAL].end(), normalLines.begin(), normalLines.end());
	
}
void Geometry::createPolyCalcNormalLlines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC& normalColor)
{	
	std::vector<Line> normalLines = this->calcPolyNormalLine(normalColor);
	lines[LineVectorIndex::POLY_CALC_NORNAL].insert(lines[LineVectorIndex::POLY_CALC_NORNAL].end(), normalLines.begin(), normalLines.end());
}

//void Geometry::calVertexNormal()
//{
//	struct KeyHash {
//		std::size_t operator()(const Vector3 key) const {
//			
//			std::hash<float> hasher;
//			return hasher(key.x) ^ (hasher(key.y) << 1) ^ (hasher(key.z) << 2);
//		}
//	};
//
//	struct KeyEqual {
//		bool operator()(const Vector3& lhs,
//			const Vector3&& rhs) const {
//			return lhs == rhs;
//		}
//	};
//
//	std::unordered_map<Vector3, std::vector<std::pair<PolygonGC*, Vertex*>>, KeyHash, KeyEqual> map;
//
//	// Add elements
//
//	
//	for (PolygonGC* poly : m_polygons) {
//		//std::pair<PolygonGC*, std::vector<Vertex*>> t(poly, poly->getVertexVector());
//		std::vector <Vertex*> vertexVector = poly->getVertexVector();
//		for (Vertex* vertex : vertexVector)
//		{
//			map[vertex->loc()].push_back(std::pair<PolygonGC*, Vertex*>(poly, vertex));
//		}
//	}
//
//
//	for (std::pair<Vector3,std::vector<std::pair<PolygonGC*, Vertex*>>> pair : map)
//	{
//		std::vector<std::pair<PolygonGC*, Vertex*>> vec = pair.second;
//		Vector3 avrageNormal(0, 0, 0);
//		for (std::pair<PolygonGC*, Vertex*> t : vec)
//		{
//			avrageNormal= avrageNormal + t.first->getCalcNormal();
//		}
//		avrageNormal = avrageNormal * (1 / vec.size());
//		for (std::pair<PolygonGC*, Vertex*> t : vec)
//		{
//			t.second->setDataNormal(avrageNormal);
//		}
//	}
//	
//}
//


void Geometry::loadLines(std::vector<Line> lines[LineVectorIndex::LAST], const ColorGC& bBoxColor, const ColorGC& normalColor, RenderMode renderMode)
{
	if (renderMode.getRenderShape())
	{
		this->createShapesLines(lines);
	}
	if (renderMode.getRenderObjBbox())
	{
		this->createObjBboxLines(lines, bBoxColor);
	}
	if (renderMode.getRenderPolygonsBbox())
	{
		this->createPolyBboxLines(lines, bBoxColor);
	}
	if (renderMode.getRenderPolygonsCalcNormal())
	{
		this->createPolyCalcNormalLlines(lines, normalColor);
	}
	if (renderMode.getRenderPolygonsNormalFromData())
	{
		this->createPolyNormalLlinesFromData(lines, normalColor);
	}
}

std::vector<Line> Geometry::getPolyNormalLineFromData(const ColorGC& normalColor)
{
	std::vector<Line> lines;
	for (auto t : m_polygons)
	{
		lines.push_back( t->getNormalLineFromData(normalColor));
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