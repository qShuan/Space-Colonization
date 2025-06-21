#include "Branch.h"

Branch::Branch(Branch* parent, sf::Vector2f position, sf::Vector2f direction) : m_length(15.f), m_count(0) {

	m_parent = parent;
	m_position = position;
	m_direction = direction;
	m_original_direction = m_direction;
}

Branch::Branch(const Branch& other) : m_length(15.f) {

	m_parent = other.m_parent;
	m_position = other.m_position;
	m_direction = other.m_direction;
	m_original_direction = other.m_original_direction;
	m_count = other.m_count;
}

Branch& Branch::operator=(const Branch& other) {

	if (this == &other) return *this;

	m_parent = other.m_parent;
	m_position = other.m_position;
	m_direction = other.m_direction;
	m_original_direction = other.m_original_direction;
	m_count = other.m_count;

	return *this;
}

bool Branch::operator==(const Branch& other) const {

	if (m_position == other.m_position && m_direction == other.m_direction) return true;

	return false;
}

Branch Branch::Next() {

	sf::Vector2f newDirection = { m_direction.x * m_length, m_direction.y * m_length };
	sf::Vector2f newPosition = m_position + newDirection;

	return Branch(this, newPosition, m_direction);
}

void Branch::Reset() {

	m_direction = m_original_direction;
	m_count = 0;
}