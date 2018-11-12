#pragma once

#include <SFML/Graphics.hpp>
#include <random>

class SnakeFood
{
public:
	SnakeFood() = default;
	SnakeFood(int blockSize, sf::Vector2i initialPlayfieldSize, sf::Vector2i initialPlayfieldOffset);
	~SnakeFood();

	/*Draw snakefood inside the window */
	void render(sf::RenderWindow & renderWindow);

	/*Read coordinates of the snakefood*/
	sf::Vector2i getPosition();
	
	/*Place snakefood on random position inside the playfield*/
	void randomizePosition();

private:
	/*Information defining the gameworld*/
	int size;
	sf::Vector2i playfieldOffset;
	sf::Vector2i playfieldSize;

	/*State of the snakefood*/
	sf::Vector2i position;
	sf::RectangleShape segmentRectangle;
};

