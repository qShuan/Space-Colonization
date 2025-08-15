#pragma once

#include <SFML/Graphics.hpp>
#include "SFML_Utils.hpp"

class Leaf {

private:

	sf::Sprite m_sprite;
	sf::Texture m_sprite_texture;

	sf::Vector2f m_position;

public:

	Leaf(sf::Vector2f position, float rotation);
	~Leaf() = default;

	void Draw(sf::RenderTarget& target);

	sf::Vector2f& GetPosition() { return m_position; }
	float GetRotation() { return m_sprite.getRotation(); }
};