#include "ThickLine.h"

ThickLine::ThickLine() 
    : m_number_of_vertices(18),
    m_thickness(1.f),
    m_color(sf::Color::White) {

    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(m_number_of_vertices);

    SetLineColor(m_color);
}

void ThickLine::SetLinePosition(sf::Vector2f beginPosition, sf::Vector2f endPosition) {

	m_begin_position = beginPosition;
	m_end_position = endPosition;

    Update();
}

void ThickLine::SetLineColor(sf::Color color) {

    m_color = color;

    for (int i = 0; i < m_number_of_vertices; i++)
        m_vertices[i].color = m_color;
}

void ThickLine::SetThickness(float thickness) {

    m_thickness = thickness;
    Update();
}

// Unfortunately SFML doesn't support indexed vertices so there will be vertex copies
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

    sf::Vector2f topBottomOffset = (m_thickness / 2.f) * normalizedDirection;

    // Left triangle
    m_vertices[6].position = m_end_position - offset;
    m_vertices[7].position = m_end_position + topBottomOffset - (offset / 2.f);
    m_vertices[8].position = m_end_position + topBottomOffset + (offset / 2.f);

    // Right triangle
    m_vertices[9].position = m_end_position + topBottomOffset + (offset / 2.f);
    m_vertices[10].position = m_end_position + offset;
    m_vertices[11].position = m_end_position - offset;

    /* BOTTOM TRAPEZOID */

    // Left triangle
    m_vertices[12].position = m_begin_position - topBottomOffset - (offset / 2.f);
    m_vertices[13].position = m_begin_position - offset;
    m_vertices[14].position = m_begin_position + offset;

    // Right triangle
    m_vertices[15].position = m_begin_position + offset;
    m_vertices[16].position = m_begin_position - topBottomOffset + (offset / 2.f);
    m_vertices[17].position = m_begin_position - topBottomOffset - (offset / 2.f);
}