#include "Tree.h"
#include <iostream>

Tree::Tree() 
	: m_root(nullptr), 
	m_has_tree_grown(false), 
	m_have_leaves_grown(false) {

	// Prepare the texture
	m_leaf_texture.loadFromFile("./Textures/leaf.png");
	m_leaf_render_states.texture = &m_leaf_texture;

	InitBranchesVA();
}

Tree::~Tree() {

	for (Branch* branch : m_branches) {
		delete branch;
	}
	m_branches.clear();

	for (Leaf* leaf : m_leaves) {
		delete leaf;
	}
	m_leaves.clear();
}

// How deep is the branch (from crown to root)
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

	float recordDistanceToAttractor = 1000000;
	for (size_t i = 0; i < m_attractors.size(); i++) {

		Attractor& attractor = m_attractors[i];
		float distanceToAttractor = utils::vec2::GetMagnitude(attractor.GetPosition() - branch->GetPosition());

		if (distanceToAttractor < recordDistanceToAttractor) {
			
			closestAttractor = &attractor;
		}
	}

	return closestAttractor;
}

// Create a root that goes towards the closest attractor
void Tree::CreateRoot(sf::Vector2f position) {

	if (!m_branches.empty()) 
		return;

	m_root = new Branch(nullptr, position, { 0.f, -1.f }, 0, m_tree_cfg.base_branch_color);
	m_branches.emplace_back(m_root);

	Attractor* closestAttractor = GetClosestAttractorToBranch(m_root);

	if (closestAttractor == nullptr) 
		return;

	bool isAttractorFound = false;
	Branch* currentBranch = m_root;

	// Loop through every attractor until we find one within max distance
	while (!isAttractorFound) {

		for (size_t i = 0; i < m_attractors.size(); i++) {

			Attractor& attractor = m_attractors[i];
			float distanceToAttractor = utils::vec2::GetMagnitude(attractor.GetPosition() - currentBranch->GetPosition());

			if (distanceToAttractor <= m_tree_cfg.GetMaxDistanceToAttractor()) {
				isAttractorFound = true;
			}
		}

		// Create a new branch if the attractor was not found yet
		if (!isAttractorFound) {

			Branch* newBranch = currentBranch->Next(m_branches.size(), m_tree_cfg.base_branch_color);

			// Go towards the closest attractor
			sf::Vector2f directionToAttractor = closestAttractor->GetPosition() - newBranch->GetPosition();
			static_cast<void>(utils::vec2::Normalize(directionToAttractor));

			sf::Vector2f newDirection = newBranch->GetDirection() + directionToAttractor;

			static_cast<void>(utils::vec2::Randomize(newDirection, m_tree_cfg.branch_direction_randomness_magnitude));
			static_cast<void>(utils::vec2::Normalize(newDirection));

			newBranch->SetDirection(newDirection);

			m_branches.emplace_back(newBranch);

			currentBranch = newBranch;

			// Update the vertex array
			UpdateBranchesVA(m_branches.size() - 1);
		}
	}
}

// Generate attractors randomly inside a polygon (brute force - not very optimized)
void Tree::GenerateAttractors(Polygon& polygon) {

	m_attractors.clear();

	float minX = FLT_MAX, minY = FLT_MAX, maxX = FLT_MIN, maxY = FLT_MIN;

	//Find max and min coordinates inside the polygon
	for (uint8_t i = 0; i < polygon.GetVertexCount(); i++) {

		Point currentVertex = polygon.GetVertex(static_cast<int>(i));

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

	// Place all attractors inside the polygon
	int i = 0;
	while(i < m_tree_cfg.number_of_attractors) {

		float randomX = utils::rng::RandomBetween(minX, maxX);
		float randomY = utils::rng::RandomBetween(minY, maxY);

		if (polygon.IsPointInsidePolygon({ randomX, randomY })) {

			Attractor newAttractor({ randomX, randomY });

			m_attractors.emplace_back(newAttractor);

			i++;
		}
	}
}

void Tree::RemoveReachedAttractors() {

	for (int i = static_cast<int>(m_attractors.size()) - 1; i >= 0; i--) {

		if (m_attractors[i].is_reached)
			m_attractors.erase(m_attractors.begin() + i);
	}
}

void Tree::CreateNewBranches() {

	bool isBranchAdded = false;
	for (int i = static_cast<int>(m_branches.size()) - 1; i >= 0; i--) {

		Branch* branch = m_branches[i];

		// If the branch was previously attracted and has less than 2 children
		if (branch->GetCount() > 0 && branch->GetChildren().size() < 2) {

			// Get the average direction
			sf::Vector2f finalDirection = branch->GetDirection() / static_cast<float>(branch->GetCount());

			static_cast<void>(utils::vec2::Randomize(finalDirection, m_tree_cfg.branch_direction_randomness_magnitude));
			static_cast<void>(utils::vec2::Normalize(finalDirection));

			branch->SetDirection(finalDirection);

			Branch* newBranch = branch->Next(m_branches.size(), m_tree_cfg.base_branch_color);
			m_branches.emplace_back(newBranch);

			// Update the vertex array
			UpdateBranchesVA(m_branches.size() - 1);

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

// After every iteration of Grow(), update the size and color of the branches
void Tree::UpdateBranches() {

	for (int i = static_cast<int>(m_branches.size()) - 1; i >= 0; i--) {

		Branch* branch = m_branches[i];

		// If the branch is a tip
		if (branch->GetChildren().size() == 0) {

			Branch* currentBranch = branch;

			// Go towards the root
			while (currentBranch->GetParent() != nullptr) {

				ThickenBranch(currentBranch);
				DarkenBranchColor(currentBranch);

				// Update the vertex array
				UpdateBranchesVAPositions(currentBranch->GetParent()->GetIndex());
				UpdateBranchesVAColors(currentBranch->GetIndex());

				currentBranch = currentBranch->GetParent();
			}
		}
	}
}

//Thanks to https://algorithmicbotany.org/papers/venation.sig2005.pdf, using Murray's law to thicken the branches
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

	branch->SetColor(utils::color::Darken(m_tree_cfg.base_branch_color, darkenAmount * darkenMultiplier, minLuminance));
}

Branch* Tree::FindClosestBranchToAttractor(Attractor& attractor) {

	Branch* closestBranch = nullptr;
	float recordDistanceToAttractor = 10000;

	for (size_t j = 0; j < m_branches.size(); j++) {

		Branch* currentBranch = m_branches[j];

		float distanceToAttractor = utils::vec2::GetMagnitude(attractor.GetPosition() - currentBranch->GetPosition());

		if (distanceToAttractor <= m_tree_cfg.GetMinDistanceToAttractor()) {

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

// Add a normalized attractor direction to the branch's direction
void Tree::PullBranchTowardsAttractor(Branch* branch, Attractor& attractor) {

	if (branch == nullptr) 
		return;

	sf::Vector2f directionToAttractor = attractor.GetPosition() - branch->GetPosition();
	static_cast<void>(utils::vec2::Normalize(directionToAttractor));

	sf::Vector2f newDirection = branch->GetDirection() + directionToAttractor;

	branch->SetDirection(newDirection);
	branch->SetCount(branch->GetCount() + 1);
}

// Main grow method
void Tree::Grow() {

	if (m_has_tree_grown) 
		return;

	for (size_t i = 0; i < m_attractors.size(); i++) {

		Attractor& currentAttractor = m_attractors[i];
		Branch* closestBranch = FindClosestBranchToAttractor(currentAttractor);

		PullBranchTowardsAttractor(closestBranch, currentAttractor);
	}

	RemoveReachedAttractors();
	
	CreateNewBranches();

	UpdateBranches();
}

// Update every branch color when user changes the base color in the GUI
void Tree::UpdateBranchesColor() {

	for (int i = static_cast<int>(m_branches.size()) - 1; i >= 0; i--) {

		Branch* branch = m_branches[i];

		// If the branch is a tip
		if (branch->GetChildren().size() == 0) {

			Branch* currentBranch = branch;

			// Go towards the root
			while (currentBranch->GetParent() != nullptr) {

				currentBranch->SetColor(m_tree_cfg.base_branch_color);
				DarkenBranchColor(currentBranch);

				UpdateBranchesVAColors(currentBranch->GetIndex());

				currentBranch = currentBranch->GetParent();
			}
		}
	}
}

// Update every leaf color when user changes the base color in the GUI
void Tree::UpdateLeavesColor() {

	for (size_t i = 0; i < m_leaves.size(); i++) {

		Leaf* leaf = m_leaves[i];

		leaf->SetColor(m_tree_cfg.base_leaf_color);
		UpdateLeavesVAColors(i);
	}
}

void Tree::GenerateLeaves() {

	if (IsGrowing() || !m_leaves.empty()) 
		return;

	for (int i = static_cast<int>(m_branches.size()) - 1; i >= 0; i--) {

		Branch* branch = m_branches[i];

		//If the branch is a tip
		if (branch->GetChildren().size() == 0) {

			for (int j = 0; j < m_tree_cfg.leaves_per_branch; j++) {

				// Random position on the branch
				sf::Vector2f positionOffset = branch->GetDirection() * utils::rng::RandomBetween(0.f, branch->GetLength());
				float randomAngle = utils::rng::RandomBetween(-60.f, 60.f);

				Leaf* newLeaf = new Leaf(branch->GetParent()->GetPosition() + positionOffset,
					randomAngle, m_tree_cfg.GetMinLeafSize(), m_tree_cfg.GetMaxLeafSize(), m_tree_cfg.base_leaf_color);

				newLeaf->SetAttachedBranch(branch);

				m_leaves.emplace_back(newLeaf);
			}
		}
	}

	InitLeavesVA();
}

// Slowly grow the leaves
void Tree::GrowLeaves(float deltaTime) {

	if (!m_has_tree_grown || m_have_leaves_grown) 
		return;

	bool haveLeavesGrown = true;
	for (size_t i = 0; i < m_leaves.size(); i++) {

		Leaf* leaf = m_leaves[i];

		leaf->Grow(deltaTime);

		// On size change, update all vertices
		UpdateLeavesVAPositions(i);

		if (!leaf->IsGrown())
			haveLeavesGrown = false;
	}

	m_have_leaves_grown = haveLeavesGrown;
}

// Initialize the vertex array for leaves
void Tree::InitLeavesVA() {

	m_leaves_va.setPrimitiveType(sf::Quads);
	m_leaves_va.resize(4 * m_leaves.size());


	for (size_t i = 0; i < m_leaves.size(); i++) {

		sf::Color& color = m_leaves[i]->GetColor();

		size_t index = i * 4;

		// Set vertices for every leaf
		UpdateLeavesVAPositions(i);

		// Reversed because SFML
		m_leaves_va[index].texCoords = { 0.f, static_cast<float>(m_leaf_texture.getSize().y) };
		m_leaves_va[index + 1].texCoords = { 0.f, 0.f };
		m_leaves_va[index + 2].texCoords = { static_cast<float>(m_leaf_texture.getSize().x), 0.f };
		m_leaves_va[index + 3].texCoords = { static_cast<float>(m_leaf_texture.getSize().x), static_cast<float>(m_leaf_texture.getSize().y) };

		for(size_t j = 0; j < 4; j++)
			m_leaves_va[index + j].color = color;
	}
}

void Tree::UpdateLeavesVAPositions(size_t index) {

	sf::Vector2f& position = m_leaves[index]->GetPosition();
	sf::Vector2f& direction = m_leaves[index]->GetAttachedBranch()->GetDirection();
	sf::Vector2f directionNormal = utils::vec2::GetNormal(direction);

	float& rotation = m_leaves[index]->GetRotation();
	float& size = m_leaves[index]->GetSize();

	size_t offsetIndex = index * 4;

	sf::Vector2f bottomLeft = position + directionNormal * size;
	sf::Vector2f bottomRight = position - directionNormal * size;
	sf::Vector2f topLeft = position - directionNormal * size + direction * size * 2.f;
	sf::Vector2f topRight = position + directionNormal * size + direction * size * 2.f;

	m_leaves_va[offsetIndex].position = bottomLeft;
	m_leaves_va[offsetIndex + 1].position = topRight;
	m_leaves_va[offsetIndex + 2].position = topLeft;
	m_leaves_va[offsetIndex + 3].position = bottomRight;

	// Rotate all points
	for (size_t j = 0; j < 4; j++)
		m_leaves_va[offsetIndex + j].position = utils::vec2::RotatePointAboutOrigin(position, m_leaves_va[offsetIndex + j].position, static_cast<float>RADIANS(rotation));
}

void Tree::UpdateLeavesVAColors(size_t index) {

	sf::Color& color = m_leaves[index]->GetColor();

	size_t offsetIndex = index * 4;

	for (size_t j = 0; j < 4; j++)
		m_leaves_va[offsetIndex + j].color = color;
}

void Tree::InitBranchesVA() {

	m_branches_va.setPrimitiveType(sf::Triangles);
}

void Tree::UpdateBranchesVA(size_t index) {

	UpdateBranchesVASize();
	UpdateBranchesVAPositions(index);
	UpdateBranchesVAColors(index);
}

void Tree::UpdateBranchesVASize() {

	m_branches_va.resize(g_number_of_thick_line_vertices * m_branches.size());
}

// Unfortunately SFML doesn't support indexed vertices so there will be vertex copies
void Tree::UpdateBranchesVAPositions(size_t index) {

	size_t offsetIndex = index * g_number_of_thick_line_vertices;

	sf::Vector2f beginPosition = m_branches[index]->GetBranchLine().GetBeginPosition();
	sf::Vector2f endPosition = m_branches[index]->GetBranchLine().GetEndPosition();
	float thickness = m_branches[index]->GetThickness();

	sf::Vector2f direction = endPosition - beginPosition;
	sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f normaliedPerpendicularDirection(-normalizedDirection.y, normalizedDirection.x);

	/* MAIN QUAD */

	sf::Vector2f offset = (thickness / 2.f) * normaliedPerpendicularDirection;

	// Left triangle
	m_branches_va[offsetIndex].position = beginPosition - offset;
	m_branches_va[offsetIndex + 1].position = endPosition - offset;
	m_branches_va[offsetIndex + 2].position = endPosition + offset;

	// Right triangle
	m_branches_va[offsetIndex + 3].position = endPosition + offset;
	m_branches_va[offsetIndex + 4].position = beginPosition + offset;
	m_branches_va[offsetIndex + 5].position = beginPosition - offset;

	/* TOP TRAPEZOID */

	sf::Vector2f topBottomOffset = (thickness / 2.f) * normalizedDirection;

	// Left triangle
	m_branches_va[offsetIndex + 6].position = endPosition - offset;
	m_branches_va[offsetIndex + 7].position = endPosition + topBottomOffset - (offset / 2.f);
	m_branches_va[offsetIndex + 8].position = endPosition + topBottomOffset + (offset / 2.f);

	// Right triangle
	m_branches_va[offsetIndex + 9].position = endPosition + topBottomOffset + (offset / 2.f);
	m_branches_va[offsetIndex + 10].position = endPosition + offset;
	m_branches_va[offsetIndex + 11].position = endPosition - offset;

	/* BOTTOM TRAPEZOID */

	// Left triangle
	m_branches_va[offsetIndex + 12].position = beginPosition - topBottomOffset - (offset / 2.f);
	m_branches_va[offsetIndex + 13].position = beginPosition - offset;
	m_branches_va[offsetIndex + 14].position = beginPosition + offset;

	// Right triangle
	m_branches_va[offsetIndex + 15].position = beginPosition + offset;
	m_branches_va[offsetIndex + 16].position = beginPosition - topBottomOffset + (offset / 2.f);
	m_branches_va[offsetIndex + 17].position = beginPosition - topBottomOffset - (offset / 2.f);
}

void Tree::UpdateBranchesVAColors(size_t index) {

	size_t offsetIndex = index * g_number_of_thick_line_vertices;

	for (int j = 0; j < 18; j++) {
		m_branches_va[offsetIndex + j].color = m_branches[index]->GetBranchLine().GetLineColor();
	}
}


void Tree::Reset() {

	m_attractors.clear();

	for (Branch* branch : m_branches) {
		delete branch;
	}
	m_branches.clear();
	m_branches_va.clear();

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

	if (m_attractors.empty()) 
		return;

	for (auto& attractor : m_attractors) {

		window->draw(attractor.GetShape());
	}
}

void Tree::DrawBranches(sf::RenderWindow* window) {

	window->draw(m_branches_va);
}

void Tree::DrawLeaves(sf::RenderWindow* window) {

	window->draw(m_leaves_va, m_leaf_render_states);
}