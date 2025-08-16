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

	float m_growth_speed;

public:

	Branch* attachedBranch;

	Leaf(sf::Vector2f position, float rotation, sf::Color color = sf::Color::Green);
	~Leaf() = default;

	void LerpSize(float speed, float deltaTime);

	bool IsGrown() { return m_size >= (m_desired_size - 0.1f); }

	sf::Vector2f& GetPosition() { return m_position; }
	float& GetRotation() { return m_rotation; }
	sf::Color& GetColor() { return m_color; }
	float& GetSize() { return m_size; }
	float& GetGrowthSpeed() { return m_growth_speed; }
};