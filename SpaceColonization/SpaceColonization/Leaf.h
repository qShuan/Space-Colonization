#pragma once

#include <SFML/Graphics.hpp>
#include "SFML_Utils.hpp"
#include "Branch.h"

class Leaf {

private:

	sf::Vector2f m_position;
	sf::Color m_color;

	float m_desired_size;

	float m_size;
	float m_rotation;

public:

	Branch* attachedBranch;

	Leaf(sf::Vector2f position, float rotation, sf::Color color = sf::Color::Green);
	~Leaf() = default;

	void LerpSize(float speed, float deltaTime);

	sf::Vector2f& GetPosition() { return m_position; }
	float& GetRotation() { return m_rotation; }
	sf::Color& GetColor() { return m_color; }
	float& GetSize() { return m_size; }
};