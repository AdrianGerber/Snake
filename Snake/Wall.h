#pragma once
#include <SFML/Graphics.hpp>


class Wall
{
public:
	Wall();
	~Wall();

	/*Draw wall on screen*/
	void render(sf::RenderWindow& renderWindow);

	/*Set position of wall*/
	void setPosition(sf::Vector2i newPosition);

	/*Set dimensions of wall*/
	void setSize(sf::Vector2i newSize);

	/*Set color of wall*/
	void setColor(sf::Color newColor);

	/*Set blocksize, pixels for one unit of size/position*/
	void setBlockSize(unsigned int newBlockSize);

	/*Check if a point is on/inside the wall*/
	bool checkIntersection(sf::Vector2i position);

private:
	/*Position and size of wall*/
	int blockSize;
	sf::Vector2i wallSize;
	sf::Vector2i wallPosition;

	/*Shape used to draw the wall*/
	sf::RectangleShape shape;
};

