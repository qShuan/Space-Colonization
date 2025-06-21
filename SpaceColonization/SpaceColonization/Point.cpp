#include "Point.h"

Point::Point() : m_position({0.f, 0.f}), m_radius(5) {

	InitShape(m_radius);
}

Point::Point(sf::Color color) : m_position({0.f, 0.f}), m_radius(5) {

	InitShape(m_radius);
	m_vertex_shape.setFillColor(color);
}

void Point::InitShape(float radius) {

	m_vertex_shape.setRadius(radius);
	m_vertex_shape.setOrigin(sf::Vector2f(radius, radius));
	m_vertex_shape.setPointCount(16);
	m_vertex_shape.setFillColor(sf::Color::Green);
	m_vertex_shape.setPosition(sf::Vector2f(0.f, 0.f));
}

void Point::SetVertexPosition(sf::Vector2f position) {

	m_position = position;
}

void Point::SetShapePosition(sf::Vector2f position) {

	m_vertex_shape.setPosition(position);
}

void Point::SetPosition(sf::Vector2f position) {

	SetShapePosition(position);
	SetVertexPosition(position);
}