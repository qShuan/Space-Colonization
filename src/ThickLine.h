#pragma once
#include <SFML/Graphics.hpp>

// Thanks to https://github.com/SFML/SFML/wiki/Source:-Line-segment-with-thickness

const size_t g_number_of_thick_line_vertices = 18;

class ThickLine {

private:

    sf::Vector2f m_begin_position;
    sf::Vector2f m_end_position;

    float m_thickness;
    sf::Color m_color;

public:

    ThickLine();
    ~ThickLine() = default;

    void SetLinePosition(sf::Vector2f beginPosition, sf::Vector2f endPosition);
    void SetLineColor(sf::Color color);
    void SetThickness(float thickness);

    float& GetThickness() { return m_thickness; }

    sf::Color& GetLineColor() { return m_color; }

    sf::Vector2f& GetBeginPosition() { return m_begin_position; }
    sf::Vector2f& GetEndPosition() { return m_end_position; }
};