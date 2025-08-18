#include "Leaf.h"
#include "RNG.h"

Leaf::Leaf(sf::Vector2f position, float rotation, float minSize, float maxSize, sf::Color color) : m_position(position),
m_rotation(rotation), m_color(color), m_size_lerp_precision(0.15f), m_attached_branch(nullptr){

	m_color = utils::color::Randomize(m_color, 15.f);
	m_desired_size = randomBetween(minSize, maxSize);
	m_size = 0.f;
	m_growth_speed = randomBetween(0.5f, 1.f);
}

void Leaf::LerpSize(float speed, float deltaTime) {

	if (IsGrown()) return;

	m_size += (m_desired_size - m_size) * speed * deltaTime;
}

void Leaf::SetColor(sf::Color color) {

	m_color = utils::color::Randomize(color, 15.f);
}