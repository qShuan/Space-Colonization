#include "Tree.h"
#include <iostream>

Tree::Tree() : min_distance(10.f), max_distance(100.f), number_of_attractors(500), m_root(nullptr), number_of_leaves(100){

}

Tree::~Tree() {

	for (Branch* branch : m_branches) {
		delete branch;
	}
	m_branches.clear();
}

Attractor* Tree::GetClosestAttractorToBranch(Branch* branch) {

	Attractor* closestAttractor = nullptr;

	float recordDistance = 1000000;
	for (int i = 0; i < m_attractors.size(); i++) {

		Attractor& attractor = m_attractors[i];
		float distance = utils::vector2f::GetVectorMagnitude(attractor.GetPosition() - branch->GetPosition());

		if (distance < recordDistance) {
			
			closestAttractor = &attractor;
		}
	}

	return closestAttractor;
}

void Tree::CreateRoot(sf::Vector2f position) {

	if (!m_branches.empty()) return;

	m_root = new Branch(nullptr, position, { 0.f, -1.f });
	m_branches.emplace_back(m_root);


	Attractor* closestAttractor = GetClosestAttractorToBranch(m_root);

	if (closestAttractor == nullptr) return;

	bool isAttractorFound = false;
	Branch* currentBranch = m_root;

	while (!isAttractorFound) {

		for (int i = 0; i < m_attractors.size(); i++) {

			Attractor& attractor = m_attractors[i];
			float distance = utils::vector2f::GetVectorMagnitude(attractor.GetPosition() - currentBranch->GetPosition());

			if (distance <= max_distance) {
				isAttractorFound = true;
			}
		}

		if (!isAttractorFound) {

			Branch* newBranch = currentBranch->Next();

			// Go towards the closest attractor
			sf::Vector2f newDirection = newBranch->GetDirection() + utils::vector2f::VectorNormalize(closestAttractor->GetPosition() - newBranch->GetPosition());
			sf::Vector2f randomDirection = { randomBetween(-1.f, 1.f), randomBetween(-1.f, 1.f) };

			float randomMagnitude = 0.25f;
			randomDirection *= randomMagnitude;

			newDirection += randomDirection;
			newDirection = utils::vector2f::VectorNormalize(newDirection);
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

	for (uint16_t i = 0; i < number_of_attractors; i++) {

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

	for (int i = m_attractors.size() - 1; i >= 0; i--) {

		if (m_attractors[i].is_reached)
			m_attractors.erase(m_attractors.begin() + i);
	}
}

void Tree::CreateNewBranches() {

	for (int i = m_branches.size() - 1; i >= 0; i--) {

		Branch* branch = m_branches[i];

		if (branch->GetCount() > 0) {

			sf::Vector2f finalDirection = branch->GetDirection() / (float)branch->GetCount();
			sf::Vector2f randomDirection = { randomBetween(-1.f, 1.f), randomBetween(-1.f, 1.f) };

			float randomMagnitude = 0.25f;
			randomDirection *= randomMagnitude;

			finalDirection += randomDirection;

			finalDirection = utils::vector2f::VectorNormalize(finalDirection);

			branch->SetDirection(finalDirection);

			Branch* newBranch = branch->Next();
			m_branches.emplace_back(newBranch);

			branch->Reset();
		}
	}
}

void Tree::ThickenBranches() {

	// Update the width of branches
	for (int i = m_branches.size() - 1; i >= 0; i--) {

		Branch* branch = m_branches[i];

		if (branch->GetChildren().size() == 0) {

			Branch* currentBranch = branch;

			while (currentBranch->GetParent() != nullptr) {

				float parentThickness = currentBranch->GetParent()->GetBranchLine().GetThickness();

				if (parentThickness < currentBranch->GetBranchLine().GetThickness() + 0.8f) {
					currentBranch->GetParent()->GetBranchLine().SetThickness(currentBranch->GetBranchLine().GetThickness() + .4f);
				}
				currentBranch = currentBranch->GetParent();
			}
		}
	}
}

void Tree::Grow() {

	if (m_attractors.empty()) return;

	for (int i = 0; i < m_attractors.size(); i++) {

		Attractor& currentAttractor = m_attractors[i];
		float recordDistance = 10000;
		Branch* closestBranch = nullptr;

		for (int j = 0; j < m_branches.size(); j++) {

			Branch* currentBranch = m_branches[j];

			float distance = utils::vector2f::GetVectorMagnitude(currentAttractor.GetPosition() - currentBranch->GetPosition());

			if (distance <= min_distance) {

				currentAttractor.is_reached = true;
				closestBranch = nullptr;

				break;
			}
			else if (distance <= recordDistance) {

				recordDistance = distance;
				closestBranch = currentBranch;
			}
		}

		// Pull the branch towards the attractor
		if (closestBranch != nullptr) {

			sf::Vector2f directionToAttractor = utils::vector2f::VectorNormalize(currentAttractor.GetPosition() - closestBranch->GetPosition());
			sf::Vector2f newDirection = closestBranch->GetDirection() + directionToAttractor;

			closestBranch->SetDirection(newDirection);
			closestBranch->SetCount(closestBranch->GetCount() + 1);
		}
	}

	RemoveReachedAttractors();
	
	CreateNewBranches();

	ThickenBranches();
}

void Tree::GenerateLeaves() {

	if (IsGrowing() || m_leaves.size() >= number_of_leaves) return;

	for (int i = m_branches.size() - 1; i >= 0; i--) {

		Branch* branch = m_branches[i];
		if (branch->GetChildren().size() == 0) {
			Leaf* newLeaf = new Leaf(branch->GetPosition(), randomBetween(-360.f, 360.f));
			m_leaves.emplace_back(newLeaf);
		}
	}
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

	m_root = nullptr;
}

void Tree::DrawAttractors(sf::RenderWindow* window) {

	if (m_attractors.empty()) return;

	for (auto& attractor : m_attractors) {

		window->draw(attractor.GetShape());
	}
}

void Tree::DrawBranches(sf::RenderWindow* window) {

	if (m_branches.empty()) return;

	for (int i = m_branches.size() - 1; i >= 0; i--) {

		if (m_branches[i]->GetParent() == nullptr) continue;

		m_branches[i]->GetBranchLine().SetLinePosition(m_branches[i]->GetParent()->GetPosition(), m_branches[i]->GetPosition());
		m_branches[i]->GetBranchLine().Draw(*window);
	}
}

void Tree::DrawLeaves(sf::RenderWindow* window) {

	for (int i = 0; i < m_leaves.size(); i++)
		m_leaves[i]->Draw(*window);
}