#include "Attractor.h"

Attractor::Attractor(sf::Vector2f position) 
	: is_reached(false) {

	InitShape(5.f);
	SetPosition(position);
	GetShape().setFillColor(sf::Color::White);
}