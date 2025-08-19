#pragma once

#include "Point.h"
#include "Line.h"

#include <utils/vec2.hpp>


class Polygon {

private:

	std::vector<Point> m_vertices;
	std::vector<Line> m_edges;

	uint8_t m_vertex_count;

private:

	float VertexCrossProduct(int index);

public:

	Polygon(sf::Vector2f position, uint8_t vertexCount, float vertexSpread);
	~Polygon() = default;

	void CreatePolygon(sf::Vector2f position, uint8_t vertexCount, float vertexSpread);

	bool IsPointInsidePolygon(sf::Vector2f point);
	bool IsPolygonConvex();

	void Draw(sf::RenderWindow* window);

	uint8_t& GetVertexCount() { return m_vertex_count; }

	std::vector<Point>& GetVertices() { return m_vertices; }
	std::vector<Line>& GetEdges() { return m_edges; }

	Point& GetVertex(int index);
	Line& GetEdge(int index);
};