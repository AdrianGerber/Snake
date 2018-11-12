#include "Wall.h"



Wall::Wall()
{
}


Wall::~Wall()
{
}

void Wall::render(sf::RenderWindow & renderWindow) {
	shape.setSize(sf::Vector2f(static_cast<float>(blockSize - 1), static_cast<float>(blockSize - 1)));

	/*Render the wall by filling it out with squares*/
	for (int xBlockPos = wallPosition.x; xBlockPos < wallPosition.x + wallSize.x; xBlockPos++) {
		for (int yBlockPos = wallPosition.y; yBlockPos < wallPosition.y + wallSize.y; yBlockPos++) {
			shape.setPosition(sf::Vector2f(static_cast<float>(xBlockPos*blockSize), static_cast<float>(yBlockPos*blockSize)));
			renderWindow.draw(shape);
		}
	}
}

void Wall::setPosition(sf::Vector2i newPosition) {
	/*Place wall at the new position*/
	wallPosition = newPosition;
}

void Wall::setSize(sf::Vector2i newSize) {
	/*Store the new size*/
	wallSize = newSize;
	/*Handle negative size values*/
	if (wallSize.x < 0) {
		wallPosition.x += wallSize.x;
		wallSize.x = -wallSize.x;
	}
	if (wallSize.y < 0) {
		wallPosition.y += wallSize.y;
		wallSize.y = -wallSize.y;
	}
}

void Wall::setColor(sf::Color newColor) {
	/*Fill the shape with the new color*/
	shape.setFillColor(newColor);
}

void Wall::setBlockSize(unsigned int newBlockSize) {
	/*Store new blocksize*/
	blockSize = newBlockSize;
}

bool Wall::checkIntersection(sf::Vector2i position) {
	/*Check if the position is within the wall*/
	if (position.x < wallPosition.x + wallSize.x && position.x >= wallPosition.x) {
		if (position.y < wallPosition.y + wallSize.y && position.y >= wallPosition.y) {
			return true;
		}
	}
	return false;
}