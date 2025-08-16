#include "Polygon.h"

Polygon::Polygon(sf::Vector2f position, uint8_t vertexCount, float vertexSpread) {

	CreatePolygon(position, vertexCount, vertexSpread);
}

void Polygon::CreatePolygon(sf::Vector2f position, uint8_t vertexCount, float vertexSpread) {

	m_vertex_count = vertexCount;

	float degrees = 360;

	for (uint8_t i = 0; i < vertexCount; i++) {

		const float x = position.x + cos((float)RADIANS(i * (degrees / vertexCount))) * vertexSpread;
		const float y = position.y + sin((float)RADIANS(i * (degrees / vertexCount))) * vertexSpread;

		Point newVertex(sf::Color::Green);
		newVertex.SetPosition({ x, y });

		m_vertices.push_back(newVertex);
	}

	for (uint8_t i = 0; i < vertexCount; i++) {

		Line newEdge;

		newEdge.SetLinePosition(m_vertices[i].GetPosition(), m_vertices[(i + 1) % vertexCount].GetPosition());
		newEdge.SetBeginVertex(&m_vertices[i]);
		newEdge.SetEndVertex(&m_vertices[(i + 1) % vertexCount]);

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

//https://math.stackexchange.com/questions/4183023/check-if-point-is-inside-a-convex-polygon-i-need-an-example-for-a-formular
bool Polygon::IsPointInsidePolygon(sf::Vector2f point) {

	std::vector<float> D;

	for (uint8_t i = 0; i < m_vertex_count; i++) {

		Line currentLine = m_edges[i];

		D.push_back((currentLine.GetLineEndPosition().x - currentLine.GetLineBeginPosition().x) *
			(point.y - currentLine.GetLineBeginPosition().y) - (point.x - currentLine.GetLineBeginPosition().x) *
			(currentLine.GetLineEndPosition().y - currentLine.GetLineBeginPosition().y));
	}

	bool hasTheSameSign = true;
	bool isNegative = (D[0] < 0);

	for (uint8_t i = 1; i < m_vertex_count; i++) {

		if ((D[i] > 0 && isNegative) || (D[i] < 0 && !isNegative)) {
			hasTheSameSign = false;
			break;
		}
	}

	return hasTheSameSign;
}

//Check if every vertex is convex
bool Polygon::IsPolygonConvex() {

	float sign = VertexCrossProduct(0);

	for (int i = 1; i < m_vertex_count; i++) {

		float cross = VertexCrossProduct(i);

		if (cross * sign < 0.f) {
			return false;
		}
	}

	return true;
}

float Polygon::VertexCrossProduct(int index) {

	Point& vertex = m_vertices[index];
	Point& prevVertex = GetVertex(index - 1);
	Point& nextVertex = GetVertex(index + 1);

	sf::Vector2f vToPrev = prevVertex.GetPosition() - vertex.GetPosition();
	sf::Vector2f vToNext = nextVertex.GetPosition() - vertex.GetPosition();

	//Swapped because SFML has flipped y-coordinates
	return utils::vec2::ZCrossProduct(vToNext, vToPrev);
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