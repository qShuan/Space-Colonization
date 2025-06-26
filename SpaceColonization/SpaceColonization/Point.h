#pragma once

#include <SFML/Graphics.hpp>

class Point {

protected:

	sf::Vector2f m_position;
	float m_radius;
	
	sf::CircleShape m_vertex_shape;

public:

	Point();
	Point(sf::Color color);
	virtual ~Point() = default;

	void InitShape(float radius);

	void SetPointPosition(sf::Vector2f position);
	void SetShapePosition(sf::Vector2f position);
	void SetPosition(sf::Vector2f position);

	sf::Vector2f GetPosition() { return m_position; }
	sf::CircleShape& GetShape() { return m_vertex_shape; }
};