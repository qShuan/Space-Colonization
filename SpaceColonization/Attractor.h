#pragma once
#include "Point.h"

class Attractor : public Point {

public:

	Attractor(sf::Vector2f position);

	bool is_reached;
};