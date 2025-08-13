#include "ThickLine.h"

ThickLine::ThickLine() : m_thickness(1.f), m_color(sf::Color::White) {

    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(NUMBER_OF_VERTICES);

    SetLineColor(m_color);
}

void ThickLine::SetLinePosition(sf::Vector2f beginPosition, sf::Vector2f endPosition) {

	m_begin_position = beginPosition;
	m_end_position = endPosition;

    Update();
}

void ThickLine::SetLineColor(sf::Color color) {

    for (int i = 0; i < NUMBER_OF_VERTICES; ++i)
        m_vertices[i].color = color;

    m_color = color;
}

void ThickLine::SetThickness(float thickness) {

    m_thickness = thickness;
    Update();
}

void ThickLine::Update() {

    sf::Vector2f direction = m_end_position - m_begin_position;
    sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normaliedPerpendicularDirection(-normalizedDirection.y, normalizedDirection.x);

    /* MAIN QUAD */

    sf::Vector2f offset = (m_thickness / 2.f) * normaliedPerpendicularDirection;

    // Left triangle
    m_vertices[0].position = m_begin_position - offset;
    m_vertices[1].position = m_end_position - offset;
    m_vertices[2].position = m_end_position + offset;

    // Right triangle
    m_vertices[3].position = m_end_position + offset;
    m_vertices[4].position = m_begin_position + offset;
    m_vertices[5].position = m_begin_position - offset;

    /* TOP TRAPEZOID */

    sf::Vector2f topOffset = (m_thickness / 2.f) * normalizedDirection;

    // Left triangle
    m_vertices[6].position = m_end_position - offset;
    m_vertices[7].position = m_end_position + topOffset - (offset / 2.f);
    m_vertices[8].position = m_end_position + topOffset + (offset / 2.f);

    // Right triangle
    m_vertices[9].position = m_end_position + topOffset + (offset / 2.f);
    m_vertices[10].position = m_end_position + offset;
    m_vertices[11].position = m_end_position - offset;
}