#pragma once
#include "Leaf.h"
#include "Branch.h"
#include "Polygon.h"
#include "RNG.h"

class Tree {

private:

	std::vector<Leaf> m_leaves;
	std::vector<Branch> m_branches;

public:

	uint16_t number_of_leaves;
	float min_distance, max_distance;

	Tree() : min_distance(50.f), max_distance(100.f), number_of_leaves(100) {}
	~Tree() = default;

	void GenerateLeaves(Polygon& polygon);

	void DrawLeaves(sf::RenderWindow* window);

	std::vector<Leaf>& GetLeaves() { return m_leaves; }
	std::vector<Branch>& GetBranches() { return m_branches; }
};