#include "Polygon.h"

Polygon::Polygon(sf::Vector2f position) 
	: m_base_space_between_vertices(350.f),
	m_vertex_count(6) {

	CreatePolygon(position);
}

void Polygon::CreatePolygon(sf::Vector2f position) {

	m_position = position;

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

void Polygon::UpdatePolygonVertices(uint8_t newVertexCount) {

	m_vertex_count = newVertexCount;
	m_edges.clear();
	m_vertices.clear();

	CreatePolygon(m_position);
}

void Polygon::Draw(sf::RenderWindow* window) {

	for (auto& vertex : m_vertices) {
		window->draw(vertex.GetShape());
	}
	for (auto& edge : m_edges) {
		window->draw(edge.GetLine(), 2, sf::Lines);
	}
}

// Thanks to https://stackoverflow.com/questions/217578/how-can-i-determine-whether-a-2d-point-is-within-a-polygon
bool Polygon::IsPointInsidePolygon(sf::Vector2f point) {

	sf::Vector2f pointRayEnd = point + sf::Vector2f(1.f, 0.f) * 1600.f;

	int intersectedEdgesCount = 0;
	for (uint8_t i = 0; i < m_vertex_count; i++) {

		Line currentLine = m_edges[i];

		sf::Vector2f lineBeginPosition = currentLine.GetLineBeginPosition();
		sf::Vector2f lineEndPosition = currentLine.GetLineEndPosition();

		float d1, d2;
		float a1, a2, b1, b2, c1, c2;

		// Convert vector 1 to a line (line 1) of infinite length.
		// We want the line in linear equation standard form: A*x + B*y + C = 0
		// See: http://en.wikipedia.org/wiki/Linear_equation
		a1 = pointRayEnd.y - point.y;
		b1 = point.x - pointRayEnd.x;
		c1 = (pointRayEnd.x * point.y) - (point.x * pointRayEnd.y);

		// Every point (x,y), that solves the equation above, is on the line,
		// every point that does not solve it, is not. The equation will have a
		// positive result if it is on one side of the line and a negative one 
		// if is on the other side of it. We insert (x1,y1) and (x2,y2) of vector
		// 2 into the equation above.
		d1 = (a1 * lineBeginPosition.x) + (b1 * lineBeginPosition.y) + c1;
		d2 = (a1 * lineEndPosition.x) + (b1 * lineEndPosition.y) + c1;

		// If d1 and d2 both have the same sign, they are both on the same side
		// of our line 1 and in that case no intersection is possible. Careful, 
		// 0 is a special case, that's why we don't test ">=" and "<=", 
		// but "<" and ">".
		if (d1 > 0 && d2 > 0) continue;
		if (d1 < 0 && d2 < 0) continue;

		// The fact that vector 2 intersected the infinite line 1 above doesn't 
		// mean it also intersects the vector 1. Vector 1 is only a subset of that
		// infinite line 1, so it may have intersected that line before the vector
		// started or after it ended. To know for sure, we have to repeat the
		// the same test the other way round. We start by calculating the 
		// infinite line 2 in linear equation standard form.
		a2 = lineEndPosition.y - lineBeginPosition.y;
		b2 = lineBeginPosition.x - lineEndPosition.x;
		c2 = (lineEndPosition.x * lineBeginPosition.y) - (lineBeginPosition.x * lineEndPosition.y);

		// Calculate d1 and d2 again, this time using points of vector 1.
		d1 = (a2 * point.x) + (b2 * point.y) + c2;
		d2 = (a2 * pointRayEnd.x) + (b2 * pointRayEnd.y) + c2;

		// Again, if both have the same sign (and neither one is 0),
		// no intersection is possible.
		if (d1 > 0 && d2 > 0) continue;
		if (d1 < 0 && d2 < 0) continue;

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