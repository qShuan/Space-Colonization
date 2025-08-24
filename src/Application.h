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

const WindowConfig g_window_config;

class Application {

private:

	std::vector<Line*> m_selected_edges;

	sf::RenderWindow* m_window;

	Tree m_tree;

	Point* m_selected_vertex;
	Polygon* m_polygon;

	UserGUI m_user_gui;

	float m_base_branch_color[3];
	float m_base_leaf_color[3];

	float m_polygon_vertex_grab_radius;

	bool m_is_vertex_selected;
	bool m_should_tree_grow;
	bool m_should_render_gizmos;
	bool m_should_render_attractors;

private:

	void HandleEvents(sf::Event& event);
	void GrabPolygonVertex(sf::Event& event);
	void PullVertex();

	bool InBounds(sf::Vector2f position);

	void HandleGUIMenu();

public:

	Application();
	~Application();

	void Run();
};