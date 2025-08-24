#pragma once

#include "Point.h"
#include "Line.h"

#include <utils/vec2.hpp>

class Polygon {

private:

	std::vector<Point> m_vertices;
	std::vector<Line> m_edges;

	sf::Vector2f m_position;

	float m_base_space_between_vertices;
	uint8_t m_vertex_count;

public:

	Polygon(sf::Vector2f position);
	~Polygon() = default;

	void CreatePolygon(sf::Vector2f position);

	void UpdatePolygonVertices(uint8_t newVertexCount);

	bool IsPointInsidePolygon(sf::Vector2f point);

	void Draw(sf::RenderWindow* window);

	uint8_t& GetVertexCount() { return m_vertex_count; }

	std::vector<Point>& GetVertices() { return m_vertices; }
	std::vector<Line>& GetEdges() { return m_edges; }

	Point& GetVertex(int index);
	Line& GetEdge(int index);
};