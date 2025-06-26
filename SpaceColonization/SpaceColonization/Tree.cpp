#include "Tree.h"

Tree::~Tree() {
	delete m_root;
}

void Tree::CreateRoot(sf::Vector2f position) {

	m_root = new Branch(nullptr, position, { 0.f, -1.f });
	m_branches.push_back(m_root);
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

void Tree::DrawLeaves(sf::RenderWindow* window) {

	if (m_leaves.empty()) return;

	for (auto& leaf : m_leaves) {

		window->draw(leaf.GetShape());
	}
}

void Tree::DrawBranches(sf::RenderWindow* window) {

	if (m_branches.empty()) return;

	for (auto& branch : m_branches) {

		//Debug draw position
		sf::CircleShape circle;
		circle.setRadius(2.f);
		circle.setOrigin({ 2.f, 2.f });
		circle.setPointCount(16);
		circle.setPosition(branch->GetPosition());
		circle.setFillColor(sf::Color::White);

		window->draw(circle);

		if (branch->GetParent() == nullptr) continue;

		branch->GetBranchLine().SetLinePosition(branch->GetParent()->GetPosition(), branch->GetPosition());
		branch->GetBranchLine().SetLineColor(sf::Color::White);

		window->draw(branch->GetBranchLine().GetLine(), 2, sf::Lines);

	}
}