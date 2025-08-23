#include "Polygon.h"

Polygon::Polygon(sf::Vector2f position) 
	: m_base_space_between_vertices(350.f),
	m_vertex_count(6) {

	CreatePolygon(position);
}

void Polygon::CreatePolygon(sf::Vector2f position) {


	float degrees = 360.f;

	// Create vertices
	for (uint8_t i = 0; i < m_vertex_count; i++) {

		const float x = position.x + cos(static_cast<float>(RADIANS(i * (degrees / m_vertex_count)))) * m_base_space_between_vertices;
		const float y = position.y + sin(static_cast<float>(RADIANS(i * (degrees / m_vertex_count)))) * m_base_space_between_vertices;

		Point newVertex(sf::Color::Green);
		newVertex.SetPosition({ x, y });

		m_vertices.push_back(newVertex);
	}

	// Create the edges
	for (uint8_t i = 0; i < m_vertex_count; i++) {

		Line newEdge;

		newEdge.SetLinePosition(m_vertices[i].GetPosition(), m_vertices[(i + 1) % m_vertex_count].GetPosition());
		newEdge.SetBeginVertex(&m_vertices[i]);
		newEdge.SetEndVertex(&m_vertices[(i + 1) % m_vertex_count]);

		m_edges.push_back(newEdge);
	}
}

void Polygon::Draw(sf::RenderWindow* window) {

	for (auto& vertex : m_vertices) {
		window->draw(vertex.GetShape());
	}
	for (auto& edge : m_edges) {
		window->draw(edge.GetLine(), 2, sf::Lines);
	}
}

// Thanks to https://www.youtube.com/watch?v=5FkOO1Wwb8w
bool Polygon::IsPointInsidePolygon(sf::Vector2f point) {

	sf::Vector2f pointRayEnd = point + sf::Vector2f(1.f, 0.f) * 1600.f;

	int intersectedEdgesCount = 0;
	for (uint8_t i = 0; i < m_vertex_count; i++) {

		Line currentLine = m_edges[i];

		sf::Vector2f lineBeginPosition = currentLine.GetLineBeginPosition();
		sf::Vector2f lineEndPosition = currentLine.GetLineEndPosition();

		sf::Vector2f AC = lineBeginPosition - point;
		sf::Vector2f AB = pointRayEnd - point;
		sf::Vector2f CD = lineEndPosition - lineBeginPosition;

		float denominator = utils::vec2::CrossProduct(AB, CD);
		if (denominator == 0.f) {

			intersectedEdgesCount++;
			continue;
		}

		float t1 = utils::vec2::CrossProduct(AC, CD) / denominator;
		float t2 = utils::vec2::CrossProduct(AC, AB) / denominator;

		if (t1 >= 0.f && t1 <= 1.f && t2 >= 0.f && t2 <= 1.f)
			intersectedEdgesCount++;
	}

	return (intersectedEdgesCount % 2 != 0);
}

Point& Polygon::GetVertex(int index) {

	if (index >= m_vertex_count)
		return m_vertices[index % m_vertex_count];
	else if (index < 0)
		return m_vertices[index % m_vertex_count + m_vertex_count];

	return m_vertices[index];
}

Line& Polygon::GetEdge(int index) {

	if (index >= m_vertex_count)
		return m_edges[index % m_vertex_count];
	else if (index < 0)
		return m_edges[index % m_vertex_count + m_vertex_count];

	return m_edges[index];
}