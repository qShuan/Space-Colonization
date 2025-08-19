#include "Branch.h"
#include <iostream>

Branch::Branch(Branch* parent, sf::Vector2f position, sf::Vector2f direction, sf::Color color) : m_length(10.f), m_count(0), 
m_parent(parent),
m_position(position),
m_direction(direction),
m_original_direction(direction) {

	SetColor(color);
}

Branch::Branch(const Branch& other) : m_length(10.f),
m_parent(other.m_parent),
m_position(other.m_position),
m_direction(other.m_direction),
m_original_direction(other.m_original_direction),
m_count(other.m_count),
m_children(other.m_children){

}

Branch& Branch::operator=(const Branch& other) {

	if (this == &other) return *this;

	m_parent = other.m_parent;
	m_children = other.m_children;
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

// Create new branch at the end of current branch
Branch* Branch::Next(sf::Color nextColor) {

	sf::Vector2f newDirection = m_direction * m_length;
	sf::Vector2f newPosition = m_position + newDirection;

	Branch* nextBranch = new Branch(this, newPosition, m_direction, nextColor);

	m_children.emplace_back(nextBranch);

	return nextBranch;
}

// Go back to the original direction and reset count
void Branch::Reset() {

	m_direction = m_original_direction;
	m_count = 0;
}