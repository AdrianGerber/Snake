#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "SnakeFood.h"

enum class Direction{Up, Down, Left, Right, None};

class Snake
{
public:
	Snake(int blockSize = 40);
	~Snake();

	/*Change the snake's direction*/
	void changeDirection(Direction newDirection);

	/*Read position of the snake's head*/
	sf::Vector2i getHeadPosition();

	/*Check if the snake can eat a given piece of food*/
	bool headIntersectsFood(SnakeFood & food);

	/*Check if the piece of food is on the snake's body*/
	bool snakeIntersectsFood(SnakeFood & food);

	/*Check whether and where the snake's head intersects it's body*/
	int checkForSelfIntersection();

	/*Read the number of segments belonging to the snake*/
	size_t getLength();

	/*Remove the specified number of segment from the snake's tail*/
	void cutTail(int segmentsToCut);

	/*Add the specified number of segments to the snake's tail, one segment per simulation-step*/
	void growSegments(unsigned int numberOfSegments);

	/*Reset the snake to it's starting state*/
	void reset();

	/*Handle movement and growth of the snake*/
	void update();

	/*Display the snake*/
	void render(sf::RenderWindow& renderWindow);

private:
	/*Check if the coordinates are on the snake*/
	unsigned int checkIntersectionWithBody(sf::Vector2i position);

	/*Management of the snake's direction*/
	Direction currentDirection;
	Direction futureDirection;

	/*How many new segments need to be added over the next turns?*/
	unsigned int numberOfSegmentsToGrow;

	/*Information that's defining the snake*/
	int size;
	std::vector<sf::Vector2i> snakeSegmentPositions;
	std::vector<sf::Vector2i> cutSnakeSegmentPositions;
	sf::RectangleShape segmentRectangle;
};

