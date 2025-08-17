#pragma once

#include <SFML/Graphics.hpp>
#include <utils/color.hpp>
#include "Branch.h"

#define BASE_LEAF_COLOR sf::Color(35, 128, 14)

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

	Leaf(sf::Vector2f position, float rotation, sf::Color color = sf::Color::Green);
	~Leaf() = default;

	void LerpSize(float speed, float deltaTime);

	bool IsGrown() { return m_size >= (m_desired_size - m_size_lerp_precision); }

	void SetAttachedBranch(Branch* branch) { m_attached_branch = branch; }

	Branch* GetAttachedBranch() { return m_attached_branch; }
	sf::Vector2f& GetPosition() { return m_position; }
	float& GetRotation() { return m_rotation; }
	sf::Color& GetColor() { return m_color; }
	float& GetSize() { return m_size; }
	float& GetGrowthSpeed() { return m_growth_speed; }
};