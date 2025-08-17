#pragma once
#include <SFML/Graphics.hpp>

//https://github.com/SFML/SFML/wiki/Source:-Line-segment-with-thickness

#define NUMBER_OF_VERTICES 18

class ThickLine {

private:

    sf::VertexArray m_vertices;
    float m_thickness;
    sf::Color m_color;

    sf::Vector2f m_begin_position;
    sf::Vector2f m_end_position;

public:

    ThickLine();
    ~ThickLine() = default;

    void SetLinePosition(sf::Vector2f beginPosition, sf::Vector2f endPosition);
    void SetLineColor(sf::Color color);
    void SetThickness(float thickness);

    void Update();

    void Draw(sf::RenderTarget& target)
    {
        target.draw(m_vertices);
    }

    float GetThickness() { return m_thickness; }
    sf::Color& GetLineColor() { return m_color; }
};