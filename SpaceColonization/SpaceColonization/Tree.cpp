#include "Tree.h"

void Tree::GenerateLeaves(Polygon& polygon) {

	m_leaves.clear();

	float minX = FLT_MAX, minY = FLT_MAX, maxX = FLT_MIN, maxY = FLT_MIN;

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