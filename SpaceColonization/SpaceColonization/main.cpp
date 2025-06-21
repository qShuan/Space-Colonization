

#include <iostream>
#include "Application.h"

// Brute force approach, works for now
// Try to implement ear-clipping triangulation algorithm and generate points based on the area of the triangle
/*std::vector<Point> CreateRandomPoints(Point* vertices, Line* lines, int* pointCount) {

	*pointCount = 0;

	float minX = WINDOW_WIDTH + 1, minY = WINDOW_HEIGHT + 1, maxX = -1, maxY = -1;

	for (uint8_t i = 0; i < NUMBER_OF_VERTICES; i++) {

		Point currentVertex = vertices[i];

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

	std::vector<Point> randomPoints;

	for (uint8_t i = 0; i < 100; i++) {

		float randomX = randomBetween(minX, maxX);
		float randomY = randomBetween(minY, maxY);

		if (IsPointInsidePolygon(lines, { randomX, randomY })) {

			Point newVertex(sf::Color::White);
			newVertex.SetPosition({ randomX, randomY });

			randomPoints.push_back(newVertex);
			*pointCount = *pointCount + 1;
		}
		else {
			i = i - 1;
			continue;
		}
	}

	return randomPoints;
}*/


int main() {

	Application app;

	app.Run();
	
	return 0;
}