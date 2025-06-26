#pragma once
#include "Leaf.h"
#include "Branch.h"
#include "Polygon.h"
#include "RNG.h"

class Tree {

private:

	std::vector<Leaf> m_leaves;
	std::vector<Branch*> m_branches;

	Branch* m_root;

public:

	uint16_t number_of_leaves;
	float min_distance, max_distance;

	Tree() : min_distance(50.f), max_distance(100.f), number_of_leaves(100), m_root(nullptr) {}
	~Tree();


	void CreateRoot(sf::Vector2f position);
	void GenerateLeaves(Polygon& polygon);

	void DrawLeaves(sf::RenderWindow* window);
	void DrawBranches(sf::RenderWindow* window);

	std::vector<Leaf>& GetLeaves() { return m_leaves; }
	std::vector<Branch*>& GetBranches() { return m_branches; }
};