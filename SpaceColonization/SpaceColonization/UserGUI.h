#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

#include <SFML/Graphics.hpp>

class UserGUI {

private:


public:

	UserGUI() = default;
	~UserGUI() = default;

	void Init(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window, sf::Time dt);
	void ProccessEvent(sf::RenderWindow* window, const sf::Event& event);
	void Render(sf::RenderWindow* window);
	void Close();


};