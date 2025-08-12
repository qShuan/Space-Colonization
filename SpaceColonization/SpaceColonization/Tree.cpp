#include "Tree.h"
#include <iostream>

Tree::Tree() : min_distance(10.f), max_distance(200.f), number_of_leaves(500), m_root(nullptr), max_thickness(15.f) {

}

Tree::~Tree() {

	for (Branch* branch : m_branches) {
		delete branch;
	}
	m_branches.clear();
}

float Tree::GetVectorDistance(sf::Vector2f& v1, sf::Vector2f v2) {

	float yVal = v1.y - v2.y;
	float xVal = v1.x - v2.x;

	return sqrt((yVal * yVal) + (xVal * xVal));
}

sf::Vector2f Tree::NormalizedVector(sf::Vector2f& v1, sf::Vector2f& v2) {

	sf::Vector2f newVector = v1 - v2;

	newVector /= GetVectorDistance(v1, v2);

	return newVector;
}

void Tree::CreateRoot(sf::Vector2f position) {

	if (!m_branches.empty()) return;

	m_root = new Branch(nullptr, position, { 0.f, -1.f });
	m_branches.push_back(m_root);

	bool isLeafFound = false;
	Branch* currentBranch = m_root;

	while (!isLeafFound) {

		for (int i = 0; i < m_leaves.size(); i++) {

			Leaf& leaf = m_leaves[i];
			float distance = GetVectorDistance(leaf.GetPosition(), currentBranch->GetPosition());

			if (distance <= max_distance) {
				isLeafFound = true;
			}
		}

		if (!isLeafFound) {

			Branch* newBranch = currentBranch->Next();
			m_branches.push_back(newBranch);

			currentBranch = newBranch;
		}
	}
}

void Tree::GenerateLeaves(Polygon& polygon) {

	m_leaves.clear();

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

	for (uint16_t i = 0; i < number_of_leaves; i++) {

		float randomX = randomBetween(minX, maxX);
		float randomY = randomBetween(minY, maxY);

		if (polygon.IsPointInsidePolygon({ randomX, randomY })) {

			Leaf newLeaf({ randomX, randomY });

			m_leaves.push_back(newLeaf);
		}
		else {
			i = i - 1;
			continue;
		}
	}
}

void Tree::Grow() {

	for (int i = 0; i < m_leaves.size(); i++) {

		Leaf& currentLeaf = m_leaves[i];
		float recordDistance = 10000;
		Branch* closestBranch = nullptr;

		for (int j = 0; j < m_branches.size(); j++) {

			Branch* currentBranch = m_branches[j];

			float distance = GetVectorDistance(currentLeaf.GetPosition(), currentBranch->GetPosition());


			if (distance <= min_distance) {

				currentLeaf.is_reached = true;
				closestBranch = nullptr;

				break;
			}
			else if (distance <= recordDistance) {

				recordDistance = distance;
				closestBranch = currentBranch;
			}
		}

		if (closestBranch != nullptr) {

			sf::Vector2f directionToLeaf = NormalizedVector(currentLeaf.GetPosition(), closestBranch->GetPosition());
			sf::Vector2f newDirection = closestBranch->GetDirection() + directionToLeaf;

			closestBranch->SetDirection(newDirection);
			closestBranch->SetCount(closestBranch->GetCount() + 1);
		}
	}

	for (int i = m_leaves.size() - 1; i >= 0; i--) {

		if (m_leaves[i].is_reached)
			m_leaves.erase(m_leaves.begin() + i);
	}
	for (int i = m_branches.size() - 1; i >= 0; i--) {

		Branch* branch = m_branches[i];

		if (branch->GetCount() > 0) {

			sf::Vector2f finalDirection = branch->GetDirection() / (float)branch->GetCount();
			branch->SetDirection(finalDirection);

			Branch* newBranch = branch->Next();
			m_branches.push_back(newBranch);

			branch->Reset();
		}
	}

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

void Tree::Reset() {

	m_leaves.clear();

	for (Branch* branch : m_branches) {
		delete branch;
	}
	m_branches.clear();
}

void Tree::DrawLeaves(sf::RenderWindow* window) {

	if (m_leaves.empty()) return;

	for (auto& leaf : m_leaves) {

		window->draw(leaf.GetShape());
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