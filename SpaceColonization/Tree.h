#pragma once
#include "Attractor.h"
#include "Branch.h"
#include "Polygon.h"
#include "RNG.h"
#include "Leaf.h"

#define LEAVES_PER_BRANCH 15

struct TreeConfig {

	sf::Color base_branch_color = sf::Color(105, 63, 21);
	sf::Color base_leaf_color = sf::Color(35, 128, 14);

	int number_of_attractors = 500;
	float min_distance_to_attractor = 10.f;
	float max_distance_to_attractor = 100.f;

	int number_of_leaves = 1;
	int leaves_per_branch = 15;
	float min_leaf_size = 20.f;
	float max_leaf_size = 30.f;

	float branch_direction_randomness_magnitude = 0.2f;
};

class Tree {

private:

	std::vector<Attractor> m_attractors;
	std::vector<Branch*> m_branches;
	std::vector<Leaf*> m_leaves;

	sf::RenderStates m_leaf_render_states;
	sf::VertexArray m_leaves_va;
	sf::Texture m_leaf_texture;

	TreeConfig m_cfg;

	Branch* m_root;

	bool m_has_tree_grown;
	bool m_have_leaves_grown;

	void RemoveReachedAttractors();

	Branch* FindClosestBranchToAttractor(Attractor& attractor);
	void PullBranchTowardsAttractor(Branch* branch, Attractor& attractor);

	void CreateNewBranches();

	void UpdateBranches();
	void ThickenBranch(Branch* branch);
	void DarkenBranchColor(Branch* branch);

	void InitLeavesVA();
	void UpdateLeavesVAPositions(int index);
	void UpdateLeavesVAColors(int index);

	int GetBranchDepth(Branch* branch);

public:

	Tree();
	~Tree();


	Attractor* GetClosestAttractorToBranch(Branch* branch);

	void CreateRoot(sf::Vector2f position);
	void GenerateAttractors(Polygon& polygon);
	void Grow();
	void GenerateLeaves();
	void GrowLeaves(float deltaTime);

	void Reset();

	void UpdateBranchesColor();
	void UpdateLeavesColor();

	void DrawAttractors(sf::RenderWindow* window);
	void DrawBranches(sf::RenderWindow* window);
	void DrawLeaves(sf::RenderWindow* window);

	void SetBaseBranchColor(sf::Color color) { m_cfg.base_branch_color = color; }
	void SetBaseLeafColor(sf::Color color) { m_cfg.base_leaf_color = color; }

	TreeConfig& GetConfig() { return m_cfg; }

	std::vector<Attractor>& GetAttractors() { return m_attractors; }
	std::vector<Branch*>& GetBranches() { return m_branches; }
	std::vector<Leaf*>& GetLeaves() { return m_leaves; }

	sf::Color& GetBaseBranchesColor() { return m_cfg.base_branch_color; }

	bool IsGrowing() { return !m_has_tree_grown; }
};