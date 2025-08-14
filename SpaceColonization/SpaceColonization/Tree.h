#pragma once
#include "Attractor.h"
#include "Branch.h"
#include "Polygon.h"
#include "RNG.h"


class Tree {

private:

	std::vector<Attractor> m_attractors;
	std::vector<Branch*> m_branches;

	Branch* m_root;

	std::map<int, float> m_thickness_map;

	sf::Color m_base_branches_color;

	void RemoveReachedAttractors();
	void CreateNewBranches();
	void ThickenBranches();

public:

	uint16_t number_of_attractors;
	float min_distance, max_distance;

	Tree();
	~Tree();


	Attractor* GetClosestAttractorToBranch(Branch* branch);
	void CreateRoot(sf::Vector2f position);
	void GenerateAttractors(Polygon& polygon);
	void Grow();

	void Reset();

	void DrawAttractors(sf::RenderWindow* window);
	void DrawBranches(sf::RenderWindow* window);

	void SetBaseBranchesColor(sf::Color color) { m_base_branches_color = color; }

	std::vector<Attractor>& GetLeaves() { return m_attractors; }
	std::vector<Branch*>& GetBranches() { return m_branches; }

	sf::Color& GetBaseBranchesColor() { return m_base_branches_color; }
};