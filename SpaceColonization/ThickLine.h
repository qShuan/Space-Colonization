#pragma once
#include <SFML/Graphics.hpp>

//https://github.com/SFML/SFML/wiki/Source:-Line-segment-with-thickness

#define NUMBER_OF_VERTICES 18

class ThickLine {

private:

    sf::VertexArray m_vertices;

    sf::Vector2f m_begin_position;
    sf::Vector2f m_end_position;

    float m_thickness;
    sf::Color m_color;

public:

    ThickLine();
    ~ThickLine() = default;

    void Update();

    void Draw(sf::RenderWindow* window)
    {
        window->draw(m_vertices);
    }

    void SetLinePosition(sf::Vector2f beginPosition, sf::Vector2f endPosition);
    void SetLineColor(sf::Color color);
    void SetThickness(float thickness);

    float GetThickness() { return m_thickness; }

    sf::Color& GetLineColor() { return m_color; }
};