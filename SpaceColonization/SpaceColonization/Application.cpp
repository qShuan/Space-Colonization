#include "Application.h"
#include <iostream>

Application::Application() {

	m_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Colonization", sf::Style::Titlebar | sf::Style::Close);
	m_polygon = new Polygon(NUMBER_OF_VERTICES);
	m_selected_vertex = nullptr;
	is_vertex_selected = false;
}

Application::~Application() {

	delete m_polygon;
	delete m_window;
}

void Application::HandleEvents(sf::Event& event) {

	if (event.type == __noop) {
		m_window->close();
	}
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::R) {
			m_tree.GenerateLeaves(*m_polygon);
		}
	}

	//Grab a vertex
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left && !is_vertex_selected) {

			sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*m_window);

			for (int i = 0; i < NUMBER_OF_VERTICES; i++) {

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
					is_vertex_selected = true;

					m_selected_vertex->GetShape().setFillColor(sf::Color::Yellow);
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
			is_vertex_selected = false;
		}
	}
}

void Application::PullVertex() {

	if (is_vertex_selected) {

		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*m_window);

		sf::Vector2f originalVertexPosition = m_selected_vertex->GetPosition();
		m_selected_vertex->SetPosition(mousePos);

		if (!m_polygon->IsPolygonConvex()) {
			m_selected_vertex->SetPosition(originalVertexPosition);
		}

		for (int i = 0; i < 3; i++)
			m_selected_edges[i]->UpdateLinePositions();
	}
}

void Application::Run() {

	while (m_window->isOpen()) {

		sf::Event event;

		while (m_window->pollEvent(event)) {

			HandleEvents(event);
		}

		PullVertex();

		m_window->clear();

		m_polygon->Draw(m_window);
		m_tree.DrawLeaves(m_window);

		m_window->display();
	}
}