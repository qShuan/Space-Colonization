#include "ThickLine.h"

ThickLine::ThickLine() 
    : m_thickness(1.f),
    m_color(sf::Color::White) {

    SetLineColor(m_color);
}

void ThickLine::SetLinePosition(sf::Vector2f beginPosition, sf::Vector2f endPosition) {

	m_begin_position = beginPosition;
	m_end_position = endPosition;
}

void ThickLine::SetLineColor(sf::Color color) {

    m_color = color;
}

void ThickLine::SetThickness(float thickness) {

    m_thickness = thickness;
}