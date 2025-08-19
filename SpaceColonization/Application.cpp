#include "Application.h"
#include <iostream>

Application::Application() 
	: m_window(new sf::RenderWindow(sf::VideoMode((const unsigned int)g_window_config.width, (const unsigned int)g_window_config.height), "Space Colonization", sf::Style::Titlebar | sf::Style::Close)),
	m_polygon(new Polygon(g_window_config.simulation_center)),
	m_selected_vertex(nullptr),
	m_base_branch_color({0.f}),
	m_base_leaf_color({0.f}),
	m_polygon_vertex_grab_radius(15.f),
	m_is_vertex_selected(false), 
	m_should_tree_grow(false), 
	m_should_render_gizmos(true), 
	m_should_render_attractors(false) {

	user_gui.Init(m_window);
	user_gui.InitStyle();
}

Application::~Application() {

	delete m_polygon;
	delete m_window;
}

// Handle ImGUI and SFML events
void Application::HandleEvents(sf::Event& event) {

	user_gui.ProccessEvent(m_window, event);

	if (event.type == __noop) {
		m_window->close();
	}

	GrabPolygonVertex(event);
}

// Grab a polygon vertex and it's connected edges
void Application::GrabPolygonVertex(sf::Event& event) {

	// Grab on mouse click
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left && !m_is_vertex_selected) {

			sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*m_window);

			for (int i = 0; i < (int)m_polygon->GetVertexCount(); i++) {

				Point& vertex = m_polygon->GetVertices()[i];
				Line& prevLine = m_polygon->GetEdge(i - 1);
				Line& line = m_polygon->GetEdges()[i];
				Line& nextLine = m_polygon->GetEdge(i + 1);

				sf::Vector2f position_diff = mousePos - vertex.GetPosition();

				const float distance = std::sqrt(position_diff.x * position_diff.x + position_diff.y * position_diff.y);

				if (distance <= m_polygon_vertex_grab_radius) {

					m_selected_vertex = &vertex;
					m_selected_edges.push_back(&prevLine);
					m_selected_edges.push_back(&line);
					m_selected_edges.push_back(&nextLine);
					m_is_vertex_selected = true;

					m_selected_vertex->GetShape().setFillColor(sf::Color::Yellow);

					break;
				}
			}
		}
	}
	// Release the vertex
	else if (event.type == sf::Event::MouseButtonReleased) {

		if (event.mouseButton.button == sf::Mouse::Left) {

			if (m_selected_vertex != nullptr)
				m_selected_vertex->GetShape().setFillColor(sf::Color::Green);

			m_selected_vertex = nullptr;
			m_selected_edges.clear();
			m_is_vertex_selected = false;
		}
	}
}

// Move the selected vertex and it's connected edges to mouse position
void Application::PullVertex() {

	if (m_is_vertex_selected) {

		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*m_window);

		if (!InBounds(mousePos)) return;

		sf::Vector2f originalVertexPosition = m_selected_vertex->GetPosition();
		m_selected_vertex->SetPosition(mousePos);

		// If the polygon is no longer convex - move the vertex back
		if (!m_polygon->IsPolygonConvex()) {
			m_selected_vertex->SetPosition(originalVertexPosition);
		}

		// Make sure the lines are still connected
		for (size_t i = 0; i < 3; i++)
			m_selected_edges[i]->UpdateLinePositions();
	}
}

bool Application::InBounds(sf::Vector2f position) {

	if (position.x >= 0 && position.x <= g_window_config.simulation_area_width && position.y >= 0 && position.y <= g_window_config.height) return true;

	return false;
}

// Main loop
void Application::Run() {


	sf::Clock clock;
	sf::Clock imguiClock;

	float growTickDefaultValue = 0.025f;
	float growTickCountDown = growTickDefaultValue;

	while (m_window->isOpen()) {

		sf::Event event;

		while (m_window->pollEvent(event)) {

			HandleEvents(event);
		}

		float sec = clock.restart().asSeconds();

		user_gui.Update(m_window, imguiClock.restart());

		if(m_should_render_gizmos)
			PullVertex();

		if (m_should_tree_grow && growTickCountDown <= 0.f) {
			m_tree.Grow();
		}

		m_tree.GrowLeaves(sec);

		if (growTickCountDown <= 0.f)
			growTickCountDown = growTickDefaultValue;

		m_window->clear(sf::Color(97, 144, 255));

		if(m_should_render_attractors)
			m_tree.DrawAttractors(m_window);

		m_tree.DrawBranches(m_window);
		m_tree.DrawLeaves(m_window);

		if(m_should_render_gizmos)
			m_polygon->Draw(m_window);

		HandleGUIMenu();

		growTickCountDown -= sec;

		user_gui.Render(m_window);

		m_window->display();
	}

	user_gui.Close();
}

// The whole ImGUI menu
void Application::HandleGUIMenu() {

	ImGui::Begin("Editor tools", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	ImGui::SetWindowSize(ImVec2(g_window_config.gui_width, g_window_config.height));
	ImGui::SetWindowPos(ImVec2(g_window_config.simulation_area_width, 0.f));

	ImGui::SeparatorText("Usage");
	if (ImGui::Button("Generate")) {

		m_should_tree_grow = false;
		m_tree.Reset();
		m_tree.GenerateAttractors(*m_polygon);
		m_tree.CreateRoot({ g_window_config.simulation_center.x, g_window_config.height });
		m_should_tree_grow = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset")) {
		m_tree.Reset();
	}
	ImGui::SameLine();
	if (ImGui::Button("Close")) {
		m_window->close();
	}

	ImGui::SeparatorText("Settings");
	if (ImGui::TreeNode("Generation")) {

		if (ImGui::TreeNode("Attractors")) {

			float minDistanceToAttractor = m_tree.GetConfig().GetMinDistanceToAttractor();
			ImGui::Text("Mininum distance to attractor");
			if (ImGui::SliderFloat("##min_distance_to_attractor", &minDistanceToAttractor, 5.f, 100.f)) {

				m_tree.GetConfig().SetMinDistanceToAttractor(minDistanceToAttractor);
			}

			float maxDistanceToAttractor = m_tree.GetConfig().GetMaxDistanceToAttractor();
			ImGui::Text("Maximum distance to attractor");
			if (ImGui::SliderFloat("##max_distance_to_attractor", &maxDistanceToAttractor, 10.f, 500.f)) {

				m_tree.GetConfig().SetMaxDistanceToAttractor(maxDistanceToAttractor);
			}

			ImGui::Text("Number of attractors");
			if (ImGui::SliderInt("##num_of_attractors", &m_tree.GetConfig().number_of_attractors, 10, 1000)) {}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Branches")) {

			ImGui::Text("Direction randomness magnitude");
			if (ImGui::SliderFloat("##direction_randomness", &m_tree.GetConfig().branch_direction_randomness_magnitude, 0.0f, 1.f)) {}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Leaves")) {

			ImGui::Text("Leaves per branch");
			if (ImGui::SliderInt("##leaves_per_branch", &m_tree.GetConfig().leaves_per_branch, 1, 50)) {}

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Visuals")) {

		if (ImGui::TreeNode("Rendering")) {

			ImGui::Text("Render gizmos"); ImGui::SameLine();
			if (ImGui::Checkbox("##should_render_gizmos", &m_should_render_gizmos)) {}

			ImGui::Text("Render attractors"); ImGui::SameLine();
			if (ImGui::Checkbox("##should_render_attractors", &m_should_render_attractors)) {}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Branches")) {

			ImGui::Text("Base branch color");
			if (ImGui::ColorPicker3("##base_branch_color", m_base_branch_color)) {

				sf::Uint8 r = (sf::Uint8)(m_base_branch_color[0] * 255.f);
				sf::Uint8 g = (sf::Uint8)(m_base_branch_color[1] * 255.f);
				sf::Uint8 b = (sf::Uint8)(m_base_branch_color[2] * 255.f);

				m_tree.SetBaseBranchColor(
					sf::Color(r, g, b)
				);
				m_tree.UpdateBranchesColor();
			}
			ImGui::NewLine();

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Leaves")) {

			ImGui::Text("Base leaf color");
			if (ImGui::ColorPicker3("##base_leaf_color", m_base_leaf_color)) {

				sf::Uint8 r = (sf::Uint8)(m_base_leaf_color[0] * 255.f);
				sf::Uint8 g = (sf::Uint8)(m_base_leaf_color[1] * 255.f);
				sf::Uint8 b = (sf::Uint8)(m_base_leaf_color[2] * 255.f);

				m_tree.SetBaseLeafColor(
					sf::Color(r, g, b)
				);
				m_tree.UpdateLeavesColor();
			}
			
			float minLeafSize = m_tree.GetConfig().GetMinLeafSize();
			ImGui::Text("Mininum leaf size");
			if (ImGui::SliderFloat("##min_leaf_size", &minLeafSize, 1.f, 100.f)) {

				m_tree.GetConfig().SetMinLeafSize(minLeafSize);
			}

			float maxLeafSize = m_tree.GetConfig().GetMaxLeafSize();
			ImGui::Text("Maximum leaf size");
			if (ImGui::SliderFloat("##max_leaf_size", &maxLeafSize, 1.f, 100.f)) {
			
				m_tree.GetConfig().SetMaxLeafSize(maxLeafSize);
			}

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}

	ImGui::SeparatorText("Themes");
	user_gui.ThemeSelector();

	ImGui::End();
}