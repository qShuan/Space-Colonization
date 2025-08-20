#pragma once
#include "Attractor.h"
#include "Branch.h"
#include "Polygon.h"
#include "Leaf.h"

class TreeConfig {

private:

	float min_distance_to_attractor = 10.f;
	float max_distance_to_attractor = 100.f;

	float min_leaf_size = 20.f;
	float max_leaf_size = 30.f;

public:

	sf::Color base_branch_color = sf::Color(105, 63, 21);
	sf::Color base_leaf_color = sf::Color(35, 128, 14);

	int number_of_attractors = 500;

	int leaves_per_branch = 15;

	float branch_direction_randomness_magnitude = 0.2f;

public:

	void SetMinDistanceToAttractor(float minDistance) {
		if (minDistance >= max_distance_to_attractor) {
			min_distance_to_attractor = max_distance_to_attractor - 1;
			return;
		}

		min_distance_to_attractor = minDistance;
	}

	void SetMaxDistanceToAttractor(float maxDistance) {
		if (maxDistance <= min_distance_to_attractor) {
			max_distance_to_attractor = min_distance_to_attractor + 1;
			return;
		}

		max_distance_to_attractor = maxDistance;
	}

	void SetMinLeafSize(float minLeafSize) {
		if (minLeafSize >= max_leaf_size) {
			min_leaf_size = max_leaf_size - 1;
			return;
		}

		min_leaf_size = minLeafSize;
	}

	void SetMaxLeafSize(float maxLeafSize) {
		if (maxLeafSize <= min_leaf_size) {
			max_leaf_size = min_leaf_size + 1;
			return;
		}

		max_leaf_size = maxLeafSize;
	}

	float& GetMinDistanceToAttractor() { return min_distance_to_attractor; }
	float& GetMaxDistanceToAttractor() { return max_distance_to_attractor; }
	float& GetMinLeafSize() { return min_leaf_size; }
	float& GetMaxLeafSize() { return max_leaf_size; }
};

class Tree {

private:

	std::vector<Attractor> m_attractors;
	std::vector<Branch*> m_branches;
	std::vector<Leaf*> m_leaves;

	sf::RenderStates m_leaf_render_states;
	sf::VertexArray m_leaves_va;
	sf::Texture m_leaf_texture;

	sf::VertexArray m_branches_va;

	TreeConfig m_tree_cfg;

	Branch* m_root;

	bool m_has_tree_grown;
	bool m_have_leaves_grown;

private:

	void RemoveReachedAttractors();

	Branch* FindClosestBranchToAttractor(Attractor& attractor);
	void PullBranchTowardsAttractor(Branch* branch, Attractor& attractor);

	void CreateNewBranches();

	void UpdateBranches();
	void ThickenBranch(Branch* branch);
	void DarkenBranchColor(Branch* branch);

	void InitLeavesVA();
	void UpdateLeavesVAPositions(size_t index);
	void UpdateLeavesVAColors(size_t index);

	void InitBranchesVA();
	void UpdateBranchesVA(size_t index);
	void UpdateBranchesVASize();
	void UpdateBranchesVAPositions(size_t index);
	void UpdateBranchesVAColors(size_t index);

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

	void SetBaseBranchColor(sf::Color color) { m_tree_cfg.base_branch_color = color; }
	void SetBaseLeafColor(sf::Color color) { m_tree_cfg.base_leaf_color = color; }

	TreeConfig& GetConfig() { return m_tree_cfg; }

	std::vector<Attractor>& GetAttractors() { return m_attractors; }
	std::vector<Branch*>& GetBranches() { return m_branches; }
	std::vector<Leaf*>& GetLeaves() { return m_leaves; }

	sf::Color& GetBaseBranchesColor() { return m_tree_cfg.base_branch_color; }

	bool IsGrowing() { return !m_has_tree_grown; }
};