#pragma once

#include "Tree.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define VERTEX_MOVE_RADIUS 15
#define NUMBER_OF_VERTICES 6
#define SPACE_BETWEEN_VERTICES 350

class Application {

private:

	sf::RenderWindow* m_window;

	Polygon* m_polygon;
	Point* m_selected_vertex;
	std::vector<Line*> m_selected_edges;

	bool m_is_vertex_selected;
	bool m_should_tree_grow;

	Tree m_tree;

	void HandleEvents(sf::Event& event);
	void PullVertex();
	bool InBounds(sf::Vector2f position);

public:

	Application();
	~Application();

	void Run();
};