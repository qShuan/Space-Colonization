#include "ThickLine.h"

ThickLine::ThickLine() : m_thickness(1.f) {

    m_color = sf::Color::White;
    SetLineColor(m_color);
}

void ThickLine::SetLinePosition(sf::Vector2f beginPosition, sf::Vector2f endPosition) {

	m_begin_position = beginPosition;
	m_end_position = endPosition;

    Update();
}

void ThickLine::SetLineColor(sf::Color color) {

    for (int i = 0; i < 4; ++i)
        m_vertices[i].color = color;
}

void ThickLine::SetThickness(float thickness) {

    m_thickness = thickness;
    Update();
}

void ThickLine::Update() {

    sf::Vector2f direction = m_end_position - m_begin_position;
    sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

    sf::Vector2f offset = (m_thickness / 2.f) * unitPerpendicular;

    m_vertices[0].position = m_begin_position + offset;
    m_vertices[1].position = m_end_position + offset;
    m_vertices[2].position = m_end_position - offset;
    m_vertices[3].position = m_begin_position - offset;
}