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

	std::map<int, float> m_thickness_map;

public:

	uint16_t number_of_leaves;
	float min_distance, max_distance;
	float max_thickness;

	Tree();
	~Tree();


	void CreateRoot(sf::Vector2f position);
	void GenerateLeaves(Polygon& polygon);
	void Grow();

	void Reset();

	void DrawLeaves(sf::RenderWindow* window);
	void DrawBranches(sf::RenderWindow* window);

	float GetVectorDistance(sf::Vector2f& v1, sf::Vector2f v2);
	sf::Vector2f NormalizedVector(sf::Vector2f& v1, sf::Vector2f& v2);

	std::vector<Leaf>& GetLeaves() { return m_leaves; }
	std::vector<Branch*>& GetBranches() { return m_branches; }
};