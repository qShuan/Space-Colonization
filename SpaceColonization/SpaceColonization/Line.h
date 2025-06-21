#pragma once
#include "Point.h"

class Line {

private:

	sf::Vertex m_line[2];

	sf::Vector2f m_begin_position;
	sf::Vector2f m_end_position;

	Point* m_begin_vertex;
	Point* m_end_vertex;

public:

	Line();
	~Line() = default;

	void SetLinePosition(sf::Vector2f beginPosition, sf::Vector2f endPosition);
	void SetLineBeginPosition(sf::Vector2f beginPosition);
	void SetLineEndPosition(sf::Vector2f endPosition);

	void SetBeginVertex(Point* vertex);
	void SetEndVertex(Point* vertex);

	void SetLineColor(sf::Color color);

	void UpdateLinePositions();

	sf::Vertex* GetLine() { return m_line; }
	sf::Vector2f GetLineBeginPosition() { return m_begin_position; }
	sf::Vector2f GetLineEndPosition() { return m_end_position; }
};