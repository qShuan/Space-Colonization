#pragma once
#include "Attractor.h"
#include "Branch.h"
#include "Polygon.h"
#include "RNG.h"
#include "Leaf.h"

#define LEAVES_PER_BRANCH 15

class Tree {

private:

	std::vector<Attractor> m_attractors;
	std::vector<Branch*> m_branches;
	std::vector<Leaf*> m_leaves;

	sf::VertexArray m_leaves_va;
	sf::Texture m_leaf_texture;
	sf::RenderStates m_leaf_render_states;

	Branch* m_root;

	std::map<int, float> m_thickness_map;

	sf::Color m_base_branches_color;

	bool m_has_tree_grown;
	bool m_have_leaves_grown;

	void RemoveReachedAttractors();
	void CreateNewBranches();
	void ThickenBranches();
	void InitLeavesVA();
	void UpdateLeavesVAPositions(int index);

public:

	uint16_t number_of_attractors;
	float min_distance, max_distance;
	uint16_t number_of_leaves;

	Tree();
	~Tree();


	Attractor* GetClosestAttractorToBranch(Branch* branch);
	void CreateRoot(sf::Vector2f position);
	void GenerateAttractors(Polygon& polygon);
	void Grow();
	void GenerateLeaves();
	void GrowLeaves(float deltaTime);

	void Reset();

	void DrawAttractors(sf::RenderWindow* window);
	void DrawBranches(sf::RenderWindow* window);
	void DrawLeaves(sf::RenderWindow* window);

	void SetBaseBranchesColor(sf::Color color) { m_base_branches_color = color; }

	std::vector<Attractor>& GetAttractors() { return m_attractors; }
	std::vector<Branch*>& GetBranches() { return m_branches; }
	std::vector<Leaf*>& GetLeaves() { return m_leaves; }

	sf::Color& GetBaseBranchesColor() { return m_base_branches_color; }

	bool IsGrowing() { return !m_has_tree_grown; }
};