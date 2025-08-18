#pragma once

#include <imgui/imgui.h>
#include <imgui-styles/imgui_themes.h>
#include <imgui/imgui-SFML.h>


#include <SFML/Graphics.hpp>

#include <utils/logging.hpp>

class UserGUI {

private:

	ImGuiStyle* m_style;
	std::vector<std::string> m_theme_names;
	int m_current_theme_index;

public:

	UserGUI() = default;
	~UserGUI() = default;

	void Init(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window, sf::Time dt);
	void ProccessEvent(sf::RenderWindow* window, const sf::Event& event);
	void Render(sf::RenderWindow* window);
	void Close();

	void ThemeSelector();
	void InitStyle();
};