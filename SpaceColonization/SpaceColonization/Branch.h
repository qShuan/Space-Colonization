#pragma once
#include "Line.h"

class Branch {

private:

	Branch* m_parent;
	Line m_line;
	
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

	Branch* GetParent() { return m_parent; }
	Line& GetBranchLine() { return m_line; }
	sf::Vector2f& GetPosition() { return m_position; }
	sf::Vector2f& GetDirection() { return m_direction; }
	sf::Vector2f& GetOriginalDirection() { return m_original_direction; }
	float& GetLength() { return m_length; }
	int& GetCount() { return m_count; }
};