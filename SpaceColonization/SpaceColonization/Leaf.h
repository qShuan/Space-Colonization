#pragma once
#include "Point.h"

class Leaf : public Point {

public:

	Leaf(sf::Vector2f position);

	bool is_reached;
};