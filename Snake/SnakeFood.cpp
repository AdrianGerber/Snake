#include "SnakeFood.h"


SnakeFood::SnakeFood(int blockSize, sf::Vector2i initialPlayfieldSize, sf::Vector2i initialPlayfieldOffset)
{
	/*Store all parameters needed to draw the 'snakefood' inside the gameworld*/
	size = blockSize;
	playfieldSize = initialPlayfieldSize;
	playfieldOffset = initialPlayfieldOffset;
}

SnakeFood::~SnakeFood()
{
}

void SnakeFood::render(sf::RenderWindow & renderWindow)
{
	/*Calculate position and size of the 'snakefood'*/
	segmentRectangle.setSize(sf::Vector2f(static_cast<float>(size - 1), static_cast<float>(size - 1)));
	segmentRectangle.setPosition(sf::Vector2f(position*size));
	/*Draw 'snakefood' to the window*/
	segmentRectangle.setFillColor(sf::Color::Green);
	renderWindow.draw(segmentRectangle);
}

sf::Vector2i SnakeFood::getPosition()
{
	/*Return the coordinates of the 'snakefood'*/
	return position;
}

void SnakeFood::randomizePosition()
{
	/*Pick a random position inside the playfield*/
	unsigned int xPos = (std::rand() % playfieldSize.x) + playfieldOffset.x;
	unsigned int yPos = (std::rand() % playfieldSize.y) + playfieldOffset.y;
	/*Use it as the new position for the piece of 'snakefood'*/
	position = sf::Vector2i(xPos, yPos);
}
