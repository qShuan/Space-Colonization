#pragma once

#include "Tree.h"
#include "UserGUI.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define VERTEX_MOVE_RADIUS 15
#define NUMBER_OF_POLYGON_VERTICES 6
#define SPACE_BETWEEN_VERTICES 350

class Application {

private:

	std::vector<Line*> m_selected_edges;

	Tree m_tree;
	UserGUI userGUI;

	sf::RenderWindow* m_window;
	Polygon* m_polygon;
	Point* m_selected_vertex;

	sf::Color m_branches_base_color;

	bool m_is_vertex_selected;
	bool m_should_tree_grow;

	void HandleEvents(sf::Event& event);
	void PullVertex();
	bool InBounds(sf::Vector2f position);

public:

	Application();
	~Application();

	void Run();
};