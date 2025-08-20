#include "Leaf.h"

Leaf::Leaf(sf::Vector2f position, float rotation, float minSize, float maxSize, sf::Color color) 
	: m_attached_branch(nullptr),
	m_position(position), 
	m_color(utils::color::Randomize(color, 15.f)),
	m_desired_size(utils::rng::RandomBetween(minSize, maxSize)),
	m_size(0.f),
	m_rotation(rotation), 
	m_growth_speed(utils::rng::RandomBetween(0.5f, 1.f)),
	m_size_lerp_precision(0.15f) {

}

void Leaf::Grow(float deltaTime) {

	if (IsGrown()) return;

	// Lerp towards desired size
	m_size += (m_desired_size - m_size) * m_growth_speed * deltaTime;
}

void Leaf::SetColor(sf::Color color) {

	m_color = utils::color::Randomize(color, 15.f);
}