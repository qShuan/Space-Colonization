#include "Line.h"

Line::Line() 
	: m_begin_vertex(nullptr),
	m_end_vertex(nullptr) {

	m_line[0].color = sf::Color::Green;
	m_line[1].color = sf::Color::Green;
}

void Line::SetLinePosition(sf::Vector2f beginPosition, sf::Vector2f endPosition) {

	m_begin_position = beginPosition;
	m_end_position = endPosition;

	m_line[0].position = m_begin_position;
	m_line[1].position = m_end_position;
}

void Line::SetLineBeginPosition(sf::Vector2f beginPosition) {

	m_begin_position = beginPosition;

	m_line[0].position = m_begin_position;
}

void Line::SetLineEndPosition(sf::Vector2f endPosition) {

	m_end_position = endPosition;

	m_line[1].position = m_end_position;
}

void Line::SetBeginVertex(Point* vertex) {

	m_begin_vertex = vertex;
}

void Line::SetEndVertex(Point* vertex) {

	m_end_vertex = vertex;
}

void Line::SetLineColor(sf::Color color) {

	m_line[0].color = color;
	m_line[1].color = color;
}

void Line::UpdateLinePositions() {

	m_begin_position = m_begin_vertex->GetPosition();
	m_end_position = m_end_vertex->GetPosition();

	m_line[0].position = m_begin_position;
	m_line[1].position = m_end_position;
}

void Line::Draw(sf::RenderWindow* window) {

	window->draw(m_line, 2, sf::Lines);
}