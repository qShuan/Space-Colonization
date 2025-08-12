#pragma once
#include "Line.h"
#include "ThickLine.h"

#define MIN_BRANCH_LENGTH 10.f

class Branch {

private:

	std::vector<Branch*> m_children;

	Branch* m_parent;
	Line m_line;
	ThickLine m_thick_line;
	
	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	sf::Vector2f m_original_direction;

	float m_length;
	int m_count;

public:

	Branch(Branch* parent, sf::Vector2f position, sf::Vector2f direction);
	Branch(const Branch& other);
	~Branch() = default;

	Branch* Next();

	void Reset();

	Branch& operator=(const Branch& other);

	bool operator==(const Branch& other) const;

	void SetCount(int count) { m_count = count; }
	void SetDirection(sf::Vector2f direction) { m_direction = direction; }
	void SetParent(Branch* parent) { m_parent = parent; }

	Branch* GetParent() { return m_parent; }
	std::vector<Branch*>& GetChildren() { return m_children; }
	ThickLine& GetBranchLine() { return m_thick_line; }
	sf::Vector2f& GetPosition() { return m_position; }
	sf::Vector2f& GetDirection() { return m_direction; }
	sf::Vector2f& GetOriginalDirection() { return m_original_direction; }
	float& GetLength() { return m_length; }
	int& GetCount() { return m_count; }
};