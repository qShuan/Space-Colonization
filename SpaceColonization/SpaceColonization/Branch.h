#pragma once
#include "Line.h"

class Branch {

private:

	Branch* m_parent;
	
	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	sf::Vector2f m_original_direction;

	float m_length;
	int m_count;

public:

	Branch(Branch* parent, sf::Vector2f position, sf::Vector2f direction);
	Branch(const Branch& other);

	Branch Next();

	void Reset();

	Branch& operator=(const Branch& other);

	bool operator==(const Branch& other) const;
};