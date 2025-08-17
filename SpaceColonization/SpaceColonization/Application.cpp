#include "Application.h"
#include <iostream>

Application::Application() {

	m_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Colonization", sf::Style::Titlebar | sf::Style::Close);
	m_polygon = new Polygon(SIMULATION_CENTER, NUMBER_OF_POLYGON_VERTICES, SPACE_BETWEEN_VERTICES);
	m_selected_vertex = nullptr;
	m_is_vertex_selected = false;
	m_should_tree_grow = false;

	// TODO: Lighten up the color the further away we are from the root
	m_branches_base_color = sf::Color(64, 38, 8);

	userGUI.Init(m_window);
	userGUI.InitStyle();
}

Application::~Application() {

	delete m_polygon;
	delete m_window;
}

void Application::HandleEvents(sf::Event& event) {

	userGUI.ProccessEvent(m_window, event);

	if (event.type == __noop) {
		m_window->close();
	}
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::R) {
			m_tree.Reset();
			m_tree.GenerateAttractors(*m_polygon);
			m_tree.CreateRoot({ SIMULATION_CENTER.x, WINDOW_HEIGHT });
			m_should_tree_grow = true;
		}
	}

	//Grab a vertex
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left && !m_is_vertex_selected) {

			sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*m_window);

			for (int i = 0; i < NUMBER_OF_POLYGON_VERTICES; i++) {

				Point& vertex = m_polygon->GetVertices()[i];
				Line& prevLine = m_polygon->GetEdge(i - 1);
				Line& line = m_polygon->GetEdges()[i];
				Line& nextLine = m_polygon->GetEdge(i + 1);

				sf::Vector2f position_diff = mousePos - vertex.GetPosition();

				const float distance = std::sqrt(position_diff.x * position_diff.x + position_diff.y * position_diff.y);

				if (distance <= VERTEX_MOVE_RADIUS) {

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
	else if (event.type == sf::Event::MouseButtonReleased) {

		if (event.mouseButton.button == sf::Mouse::Left) {

			if(m_selected_vertex != nullptr)
				m_selected_vertex->GetShape().setFillColor(sf::Color::Green);

			m_selected_vertex = nullptr;
			m_selected_edges.clear();
			m_is_vertex_selected = false;
		}
	}
}

void Application::PullVertex() {

	if (m_is_vertex_selected) {

		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*m_window);

		if (!InBounds(mousePos)) return;

		sf::Vector2f originalVertexPosition = m_selected_vertex->GetPosition();
		m_selected_vertex->SetPosition(mousePos);

		if (!m_polygon->IsPolygonConvex()) {
			m_selected_vertex->SetPosition(originalVertexPosition);
		}

		for (int i = 0; i < 3; i++)
			m_selected_edges[i]->UpdateLinePositions();
	}
}

bool Application::InBounds(sf::Vector2f position) {

	if (position.x >= 0 && position.x <= SIMULATION_AREA_WIDTH && position.y >= 0 && position.y <= WINDOW_HEIGHT) return true;

	return false;
}

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

		userGUI.Update(m_window, imguiClock.restart());

		PullVertex();

		if (m_should_tree_grow && growTickCountDown <= 0.f) {
			m_tree.Grow();
		}

		m_tree.GrowLeaves(sec);

		if (growTickCountDown <= 0.f)
			growTickCountDown = growTickDefaultValue;

		m_window->clear(sf::Color(97, 144, 255));

		m_tree.DrawAttractors(m_window);
		m_tree.DrawBranches(m_window);
		m_tree.DrawLeaves(m_window);
		m_polygon->Draw(m_window);

		UpdateGUI();

		growTickCountDown -= sec;

		userGUI.Render(m_window);

		m_window->display();
	}

	userGUI.Close();
}

void Application::UpdateGUI() {

	ImGui::Begin("Editor tools", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	ImGui::SetWindowSize(ImVec2(GUI_WIDTH, WINDOW_HEIGHT));
	ImGui::SetWindowPos(ImVec2(SIMULATION_AREA_WIDTH, 0));

	ImGui::SeparatorText("Editor Tools");
	if (ImGui::Button("Close"));
	ImGui::Separator();

	if (ImGui::BeginTabBar("Generation Items")) {

		if (ImGui::BeginTabItem("Generation")) {


			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Branches")) {

			if (ImGui::ColorPicker4("Base branch color", m_base_branch_color)) {

				m_tree.SetBaseBranchColor(
					sf::Color(m_base_branch_color[0] * 255, m_base_branch_color[1] * 255,
						m_base_branch_color[2] * 255, m_base_branch_color[3] * 255)
				);
				m_tree.UpdateBranchesColor();
			}
			ImGui::NewLine();

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Leaves")) {

			if (ImGui::ColorPicker4("Base leaf color", m_base_leaf_color)) {

				m_tree.SetBaseLeafColor(
					sf::Color(m_base_leaf_color[0] * 255, m_base_leaf_color[1] * 255,
						m_base_leaf_color[2] * 255, m_base_leaf_color[3] * 255)
				);
				m_tree.UpdateLeavesColor();
			}
			ImGui::NewLine();

			ImGui::EndTabItem();
		}
	}
	ImGui::EndTabBar();

	ImGui::End();
}