#include "Leaf.h"
#include "RNG.h"

Leaf::Leaf(sf::Vector2f position, float rotation, sf::Color color) : m_position(position), m_rotation(rotation), m_color(color){

	m_color = utils::color::RandomizeColor(m_color, 15.f);
	m_desired_size = randomBetween(20.f, 30.f);
	m_size = 0.f;
	m_growth_speed = randomBetween(0.5f, 1.f);
}

void Leaf::LerpSize(float speed, float deltaTime) {

	if (m_size >= m_desired_size - 0.1f) return;

	m_size += (m_desired_size - m_size) * speed * deltaTime;
}