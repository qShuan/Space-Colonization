#pragma once

#include "Point.h"
#include "Line.h"

#include <utils/vec2.hpp>


class Polygon {

private:

	std::vector<Point> m_vertices;
	std::vector<Line> m_edges;

	uint8_t m_vertex_count;

public:

	Polygon(sf::Vector2f position, uint8_t vertexCount, float vertexSpread);
	~Polygon() = default;

	void CreatePolygon(sf::Vector2f position, uint8_t vertexCount, float vertexSpread);
	void Draw(sf::RenderWindow* window);

	bool IsPointInsidePolygon(sf::Vector2f point);
	bool IsPolygonConvex();

	float VertexCrossProduct(int index);

	inline uint8_t& GetVertexCount() { return m_vertex_count; }
	inline std::vector<Point>& GetVertices() { return m_vertices; }
	inline std::vector<Line>& GetEdges() { return m_edges; }
	Point& GetVertex(int index);
	Line& GetEdge(int index);
};