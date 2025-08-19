#pragma once

#include <SFML/Graphics.hpp>
#include <utils/color.hpp>
#include "Branch.h"

class Leaf {

private:

	Branch* m_attached_branch;

	sf::Vector2f m_position;
	sf::Color m_color;

	float m_desired_size;

	float m_size;
	float m_rotation;

	float m_growth_speed;

	float m_size_lerp_precision;

public:

	Leaf(sf::Vector2f position, float rotation, float minSize, float maxSize, sf::Color color = sf::Color::Green);
	~Leaf() = default;

	void Grow(float speed, float deltaTime);

	void SetAttachedBranch(Branch* branch) { m_attached_branch = branch; }
	void SetColor(sf::Color color);

	Branch* GetAttachedBranch() { return m_attached_branch; }

	sf::Vector2f& GetPosition() { return m_position; }

	float& GetRotation() { return m_rotation; }
	float& GetSize() { return m_size; }
	float& GetGrowthSpeed() { return m_growth_speed; }

	sf::Color& GetColor() { return m_color; }

	bool IsGrown() { return m_size >= (m_desired_size - m_size_lerp_precision); }
};