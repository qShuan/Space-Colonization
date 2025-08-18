#pragma once
#include "Point.h"

class Line {

private:

	sf::Vertex m_line[2];

	Point* m_begin_vertex;
	Point* m_end_vertex;

	sf::Vector2f m_begin_position;
	sf::Vector2f m_end_position;

public:

	Line();
	~Line() = default;


	void UpdateLinePositions();

	void Draw(sf::RenderWindow* window);

	void SetBeginVertex(Point* vertex);
	void SetEndVertex(Point* vertex);

	void SetLinePosition(sf::Vector2f beginPosition, sf::Vector2f endPosition);
	void SetLineBeginPosition(sf::Vector2f beginPosition);
	void SetLineEndPosition(sf::Vector2f endPosition);

	void SetLineColor(sf::Color color);

	sf::Vertex* GetLine() { return m_line; }
	sf::Vector2f GetLineBeginPosition() { return m_begin_position; }
	sf::Vector2f GetLineEndPosition() { return m_end_position; }
};