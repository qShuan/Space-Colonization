#pragma once

#include <SFML/Graphics.hpp>

class Point {

private:

	sf::CircleShape m_vertex_shape;

	sf::Vector2f m_position;
	float m_radius;

public:

	Point();
	Point(sf::Color color);
	virtual ~Point() = default;

	void InitShape(float radius);

	void SetPointPosition(sf::Vector2f position);
	void SetShapePosition(sf::Vector2f position);
	void SetPosition(sf::Vector2f position);

	sf::Vector2f& GetPosition() { return m_position; }
	sf::CircleShape& GetShape() { return m_vertex_shape; }
};