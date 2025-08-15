#include "Leaf.h"
#include "RNG.h"

Leaf::Leaf(sf::Vector2f position, float rotation) : m_position(position) {

	m_sprite_texture.loadFromFile("./Textures/leaf.png");
	m_sprite.setTexture(m_sprite_texture);

	float randomSize = randomBetween(0.1f, 0.2f);
	m_sprite.setScale({ randomSize, randomSize });

	m_sprite.setOrigin({ (float)m_sprite_texture.getSize().x / 2.f, (float)m_sprite_texture.getSize().y * 0.95f});
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(rotation);

	m_sprite.setColor(utils::color::RandomizeColor(sf::Color::Green));
}

void Leaf::Draw(sf::RenderTarget& target) {

	target.draw(m_sprite);
}