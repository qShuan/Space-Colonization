#pragma once
#include <SFML/Graphics.hpp>

//https://github.com/SFML/SFML/wiki/Source:-Line-segment-with-thickness

class ThickLine {

private:

    sf::Vertex m_vertices[4];
    float m_thickness;
    sf::Color m_color;

    sf::Vector2f m_begin_position;
    sf::Vector2f m_end_position;

public:

    ThickLine();
    ~ThickLine() = default;

    ThickLine(const sf::Vector2f& point1, const sf::Vector2f& point2) :
        m_color(sf::Color::White), m_thickness(5.f)
    {
        sf::Vector2f direction = point2 - point1;
        sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

        sf::Vector2f offset = (m_thickness / 2.f) * unitPerpendicular;

        m_vertices[0].position = point1 + offset;
        m_vertices[1].position = point2 + offset;
        m_vertices[2].position = point2 - offset;
        m_vertices[3].position = point1 - offset;

        for (int i = 0; i < 4; ++i)
            m_vertices[i].color = m_color;
    }

    void SetLinePosition(sf::Vector2f beginPosition, sf::Vector2f endPosition);
    void SetLineColor(sf::Color color);
    void SetThickness(float thickness);

    void Update();

    void Draw(sf::RenderTarget& target)
    {
        target.draw(m_vertices, 4, sf::Quads);
    }

    float GetThickness() { return m_thickness; }
};