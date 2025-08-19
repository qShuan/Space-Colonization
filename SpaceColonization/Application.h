#pragma once

#include "Tree.h"
#include "UserGUI.h"

struct WindowConfig {

	const float width = 1600;
	const float height = 900;

	const float gui_width = 400;

	const float simulation_area_width = width - gui_width;
	const sf::Vector2f simulation_center = sf::Vector2f(simulation_area_width / 2.f, height / 2.f);
};

const WindowConfig g_WindowConfig;

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

private:

	void HandleEvents(sf::Event& event);
	void PullVertex();

	bool InBounds(sf::Vector2f position);

	void UpdateGUI();

public:

	Application();
	~Application();

	void Run();
};