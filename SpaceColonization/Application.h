#pragma once

#include "Tree.h"
#include "UserGUI.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define GUI_WIDTH 400

#define SIMULATION_AREA_WIDTH (WINDOW_WIDTH - GUI_WIDTH)
#define SIMULATION_CENTER sf::Vector2f((WINDOW_WIDTH - GUI_WIDTH) / 2.f, WINDOW_HEIGHT / 2.f)

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

	float m_base_branch_color[4] = { 0.f };
	float m_base_leaf_color[4] = { 0.f };

	bool m_is_vertex_selected;
	bool m_should_tree_grow;
	bool m_should_render_gizmos;
	bool m_should_render_attractors;

	void HandleEvents(sf::Event& event);
	void PullVertex();

	bool InBounds(sf::Vector2f position);

	void UpdateGUI();

public:

	Application();
	~Application();

	void Run();
};