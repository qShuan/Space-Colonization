#include "Tree.h"
#include <iostream>

Tree::Tree() : m_root(nullptr), m_has_tree_grown(false){

}

Tree::~Tree() {

	for (Branch* branch : m_branches) {
		delete branch;
	}
	m_branches.clear();
}

int Tree::GetBranchDepth(Branch* branch) {

	int depth = 1;
	while (branch->GetParent() != nullptr) {

		depth++;
		branch = branch->GetParent();
	}

	return depth;
}

Attractor* Tree::GetClosestAttractorToBranch(Branch* branch) {

	Attractor* closestAttractor = nullptr;

	float recordDistance = 1000000;
	for (int i = 0; i < m_attractors.size(); i++) {

		Attractor& attractor = m_attractors[i];
		float distance = utils::vec2::GetMagnitude(attractor.GetPosition() - branch->GetPosition());

		if (distance < recordDistance) {
			
			closestAttractor = &attractor;
		}
	}

	return closestAttractor;
}

void Tree::CreateRoot(sf::Vector2f position) {

	if (!m_branches.empty()) return;

	m_root = new Branch(nullptr, position, { 0.f, -1.f }, m_cfg.base_branch_color);
	m_branches.emplace_back(m_root);

	Attractor* closestAttractor = GetClosestAttractorToBranch(m_root);

	if (closestAttractor == nullptr) return;

	bool isAttractorFound = false;
	Branch* currentBranch = m_root;

	while (!isAttractorFound) {

		for (int i = 0; i < m_attractors.size(); i++) {

			Attractor& attractor = m_attractors[i];
			float distance = utils::vec2::GetMagnitude(attractor.GetPosition() - currentBranch->GetPosition());

			if (distance <= m_cfg.max_distance_to_attractor) {
				isAttractorFound = true;
			}
		}

		if (!isAttractorFound) {

			Branch* newBranch = currentBranch->Next(m_cfg.base_branch_color);

			// Go towards the closest attractor
			sf::Vector2f directionToAttractor = closestAttractor->GetPosition() - newBranch->GetPosition();
			(void)utils::vec2::Normalize(directionToAttractor);

			sf::Vector2f newDirection = newBranch->GetDirection() + directionToAttractor;

			(void)utils::vec2::Randomize(newDirection, m_cfg.branch_direction_randomness_magnitude);
			(void)utils::vec2::Normalize(newDirection);

			newBranch->SetDirection(newDirection);

			m_branches.emplace_back(newBranch);

			currentBranch = newBranch;
		}
	}
}

void Tree::GenerateAttractors(Polygon& polygon) {

	m_attractors.clear();

	float minX = FLT_MAX, minY = FLT_MAX, maxX = FLT_MIN, maxY = FLT_MIN;

	//Find max and min coordinates inside the polygon
	for (uint8_t i = 0; i < polygon.GetVertexCount(); i++) {

		Point currentVertex = polygon.GetVertex(i);

		sf::Vector2f currentPos = currentVertex.GetPosition();

		if (currentPos.x < minX)
			minX = currentPos.x;
		if (currentPos.x > maxX)
			maxX = currentPos.x;
		if (currentPos.y < minY)
			minY = currentPos.y;
		if (currentPos.y > maxY)
			maxY = currentPos.y;
	}

	for (int i = 0; i < m_cfg.number_of_attractors; i++) {

		float randomX = randomBetween(minX, maxX);
		float randomY = randomBetween(minY, maxY);

		if (polygon.IsPointInsidePolygon({ randomX, randomY })) {

			Attractor newAttractor({ randomX, randomY });

			m_attractors.emplace_back(newAttractor);
		}
		else {
			i = i - 1;
			continue;
		}
	}
}

void Tree::RemoveReachedAttractors() {

	for (int i = (int)m_attractors.size() - 1; i >= 0; i--) {

		if (m_attractors[i].is_reached)
			m_attractors.erase(m_attractors.begin() + i);
	}
}

void Tree::CreateNewBranches() {

	bool isBranchAdded = false;
	for (int i = (int)m_branches.size() - 1; i >= 0; i--) {

		Branch* branch = m_branches[i];

		if (branch->GetCount() > 0 && branch->GetChildren().size() < 2) {

			sf::Vector2f finalDirection = branch->GetDirection() / (float)branch->GetCount();

			(void)utils::vec2::Randomize(finalDirection, m_cfg.branch_direction_randomness_magnitude);
			(void)utils::vec2::Normalize(finalDirection);

			branch->SetDirection(finalDirection);

			Branch* newBranch = branch->Next(m_cfg.base_branch_color);
			m_branches.emplace_back(newBranch);

			isBranchAdded = true;

			branch->Reset();
		}
	}

	if (!isBranchAdded) {
		m_has_tree_grown = true;
		m_attractors.clear();

		GenerateLeaves();
	}
}

void Tree::UpdateBranches() {

	for (int i = (int)m_branches.size() - 1; i >= 0; i--) {

		Branch* branch = m_branches[i];

		// If the branch is a tip
		if (branch->GetChildren().size() == 0) {

			Branch* currentBranch = branch;

			// Go towards the root
			while (currentBranch->GetParent() != nullptr) {

				ThickenBranch(currentBranch);
				DarkenBranchColor(currentBranch);

				currentBranch = currentBranch->GetParent();
			}
		}
	}
}

void Tree::ThickenBranch(Branch* branch) {

	float parentThickness = branch->GetParent()->GetThickness();
	float branchThickness = branch->GetThickness();

	float thicknessThreshold = branchThickness + 0.8f;
	float thickenAmount = branchThickness + 0.4f;

	if (parentThickness < thicknessThreshold) {
		branch->GetParent()->SetThickness(thickenAmount);
	}
}

// Darken branch color depending on it's thickness
void Tree::DarkenBranchColor(Branch* branch) {

	float branchThickness = branch->GetThickness();

	// Reversed so we darken the thinner branches more
	float darkenAmount = 1.f / branchThickness;
	float darkenMultiplier = 100.f;
	float minLuminance = 10.f;

	branch->SetColor(utils::color::Darken(m_cfg.base_branch_color, darkenAmount * darkenMultiplier, minLuminance));
}

Branch* Tree::FindClosestBranchToAttractor(Attractor& attractor) {

	Branch* closestBranch = nullptr;
	float recordDistanceToAttractor = 10000;

	for (int j = 0; j < m_branches.size(); j++) {

		Branch* currentBranch = m_branches[j];

		float distanceToAttractor = utils::vec2::GetMagnitude(attractor.GetPosition() - currentBranch->GetPosition());

		if (distanceToAttractor <= m_cfg.min_distance_to_attractor) {

			attractor.is_reached = true;
			closestBranch = nullptr;

			break;
		}
		else if (distanceToAttractor <= recordDistanceToAttractor) {

			recordDistanceToAttractor = distanceToAttractor;
			closestBranch = currentBranch;
		}
	}

	return closestBranch;
}

void Tree::PullBranchTowardsAttractor(Branch* branch, Attractor& attractor) {

	if (branch == nullptr) return;

	sf::Vector2f directionToAttractor = attractor.GetPosition() - branch->GetPosition();
	(void)utils::vec2::Normalize(directionToAttractor);

	sf::Vector2f newDirection = branch->GetDirection() + directionToAttractor;

	branch->SetDirection(newDirection);
	branch->SetCount(branch->GetCount() + 1);
}

void Tree::Grow() {

	if (m_has_tree_grown) return;

	for (int i = 0; i < m_attractors.size(); i++) {

		Attractor& currentAttractor = m_attractors[i];
		Branch* closestBranch = FindClosestBranchToAttractor(currentAttractor);

		PullBranchTowardsAttractor(closestBranch, currentAttractor);
	}

	RemoveReachedAttractors();
	
	CreateNewBranches();

	UpdateBranches();
}

void Tree::UpdateBranchesColor() {

	for (int i = (int)m_branches.size() - 1; i >= 0; i--) {

		Branch* branch = m_branches[i];

		// If the branch is a tip
		if (branch->GetChildren().size() == 0) {

			Branch* currentBranch = branch;

			// Go towards the root
			while (currentBranch->GetParent() != nullptr) {

				currentBranch->SetColor(m_cfg.base_branch_color);
				DarkenBranchColor(currentBranch);

				currentBranch = currentBranch->GetParent();
			}
		}
	}
}

void Tree::UpdateLeavesColor() {

	for (int i = 0; i < m_leaves.size(); i++) {

		Leaf* leaf = m_leaves[i];

		leaf->SetColor(m_cfg.base_leaf_color);
		UpdateLeavesVAColors(i);
	}
}

void Tree::GenerateLeaves() {

	if (IsGrowing() || m_leaves.size() >= m_cfg.number_of_leaves) return;

	for (int i = (int)m_branches.size() - 1; i >= 0; i--) {

		Branch* branch = m_branches[i];
		if (branch->GetChildren().size() == 0) {

			for (int j = 0; j < m_cfg.leaves_per_branch; j++) {

				sf::Vector2f positionOffset = branch->GetDirection() * randomBetween(0.f, MIN_BRANCH_LENGTH);
				float randomAngle = randomBetween(-60.f, 60.f);

				Leaf* newLeaf = new Leaf(branch->GetParent()->GetPosition() + positionOffset,
					randomAngle, m_cfg.min_leaf_size, m_cfg.max_leaf_size, m_cfg.base_leaf_color);

				newLeaf->SetAttachedBranch(branch);

				m_leaves.emplace_back(newLeaf);
			}
		}
	}

	InitLeavesVA();
}

void Tree::GrowLeaves(float deltaTime) {

	if (!m_has_tree_grown || m_have_leaves_grown) return;

	bool haveLeavesGrown = true;
	for (int i = 0; i < m_leaves.size(); i++) {

		Leaf* leaf = m_leaves[i];

		leaf->LerpSize(leaf->GetGrowthSpeed(), deltaTime);

		UpdateLeavesVAPositions(i);

		if (!leaf->IsGrown())
			haveLeavesGrown = false;
	}

	m_have_leaves_grown = haveLeavesGrown;
}

void Tree::InitLeavesVA() {

	m_leaves_va.setPrimitiveType(sf::Quads);
	m_leaves_va.resize(4 * m_leaves.size());

	// Prepare the texture
	m_leaf_texture.loadFromFile("./Textures/leaf.png");
	m_leaf_render_states.texture = &m_leaf_texture;

	for (int i = 0; i < m_leaves.size(); i++) {

		sf::Color& color = m_leaves[i]->GetColor();

		int index = i * 4;

		UpdateLeavesVAPositions(i);

		// Reversed because SFML
		m_leaves_va[index].texCoords = { 0.f, (float)m_leaf_texture.getSize().y};
		m_leaves_va[index + 1].texCoords = { 0.f, 0.f };
		m_leaves_va[index + 2].texCoords = { (float)m_leaf_texture.getSize().x, 0.f };
		m_leaves_va[index + 3].texCoords = { (float)m_leaf_texture.getSize().x, (float)m_leaf_texture.getSize().y };

		for(int j = 0; j < 4; j++)
			m_leaves_va[index + j].color = color;
	}
}

void Tree::UpdateLeavesVAPositions(int index) {

	sf::Vector2f& position = m_leaves[index]->GetPosition();
	sf::Vector2f& direction = m_leaves[index]->GetAttachedBranch()->GetDirection();
	sf::Vector2f directionNormal = utils::vec2::GetNormal(direction);

	float& rotation = m_leaves[index]->GetRotation();
	float& size = m_leaves[index]->GetSize();

	int offsetIndex = index * 4;

	sf::Vector2f bottomLeft = position + directionNormal * size;
	sf::Vector2f bottomRight = position - directionNormal * size;
	sf::Vector2f topLeft = position - directionNormal * size + direction * size * 2.f;
	sf::Vector2f topRight = position + directionNormal * size + direction * size * 2.f;

	m_leaves_va[offsetIndex].position = bottomLeft;
	m_leaves_va[offsetIndex + 1].position = topRight;
	m_leaves_va[offsetIndex + 2].position = topLeft;
	m_leaves_va[offsetIndex + 3].position = bottomRight;

	// Rotate all points
	for (int j = 0; j < 4; j++)
		m_leaves_va[offsetIndex + j].position = utils::vec2::RotatePointAboutOrigin(position, m_leaves_va[offsetIndex + j].position, (float)RADIANS(rotation));
}

void Tree::UpdateLeavesVAColors(int index) {

	sf::Color& color = m_leaves[index]->GetColor();

	int offsetIndex = index * 4;

	for (int j = 0; j < 4; j++)
		m_leaves_va[offsetIndex + j].color = color;
}

void Tree::Reset() {

	m_attractors.clear();

	for (Branch* branch : m_branches) {
		delete branch;
	}
	m_branches.clear();

	for (Leaf* leaf : m_leaves) {
		delete leaf;
	}
	m_leaves.clear();
	m_leaves_va.clear();

	m_root = nullptr;
	m_has_tree_grown = false;
	m_have_leaves_grown = false;
}

void Tree::DrawAttractors(sf::RenderWindow* window) {

	if (m_attractors.empty()) return;

	for (auto& attractor : m_attractors) {

		window->draw(attractor.GetShape());
	}
}

// TODO (maybe): Refactor ThickLine to draw using one cal
void Tree::DrawBranches(sf::RenderWindow* window) {

	if (m_branches.empty()) return;

	for (int i = (int)m_branches.size() - 1; i >= 0; i--) {

		if (m_branches[i]->GetParent() == nullptr) continue;

		m_branches[i]->GetBranchLine().SetLinePosition(m_branches[i]->GetParent()->GetPosition(), m_branches[i]->GetPosition());
		m_branches[i]->GetBranchLine().Draw(window);
	}
}

void Tree::DrawLeaves(sf::RenderWindow* window) {

	window->draw(m_leaves_va, m_leaf_render_states);
}