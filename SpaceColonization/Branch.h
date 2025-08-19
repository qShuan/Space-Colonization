#pragma once
#include "Line.h"
#include "ThickLine.h"

class Branch {

private:

	std::vector<Branch*> m_children;

	Branch* m_parent;
	ThickLine m_thick_line;
	
	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	sf::Vector2f m_original_direction;

	size_t m_index;

	float m_length;
	int m_count;

public:

	Branch(Branch* parent, sf::Vector2f position, sf::Vector2f direction, size_t index, sf::Color color = sf::Color::White);
	Branch(const Branch& other);
	~Branch() = default;

	Branch* Next(size_t nextIndex, sf::Color nextColor = sf::Color::White);

	Branch& operator=(const Branch& other);

	bool operator==(const Branch& other) const;

	void Reset();

	void SetCount(int count) { m_count = count; }
	void SetDirection(sf::Vector2f direction) { m_direction = direction; }
	void SetParent(Branch* parent) { m_parent = parent; }
	void SetPosition(sf::Vector2f position) { m_position = position; }

	void SetColor(sf::Color color) { m_thick_line.SetLineColor(color); }
	void SetThickness(float thickness) { m_thick_line.SetThickness(thickness); }

	Branch* GetParent() { return m_parent; }
	std::vector<Branch*>& GetChildren() { return m_children; }

	ThickLine& GetBranchLine() { return m_thick_line; }

	sf::Vector2f& GetPosition() { return m_position; }
	sf::Vector2f& GetDirection() { return m_direction; }

	float& GetLength() { return m_length; }
	float GetThickness() { return m_thick_line.GetThickness(); }

	int& GetCount() { return m_count; }

	size_t& GetIndex() { return m_index; }
};