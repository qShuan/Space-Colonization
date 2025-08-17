#include "UserGUI.h"

void UserGUI::Init(sf::RenderWindow* window) {

	ImGui::SFML::Init(*window);
}

void UserGUI::Update(sf::RenderWindow* window, sf::Time dt){

	ImGui::SFML::Update(*window, dt);
}

void UserGUI::ProccessEvent(sf::RenderWindow* window, const sf::Event& event){
	
	ImGui::SFML::ProcessEvent(*window, event);
}

void UserGUI::Render(sf::RenderWindow* window){

	ImGui::SFML::Render(*window);
}

void UserGUI::Close() {

	ImGui::SFML::Shutdown();
}