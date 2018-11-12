#include "Snake.h"

Snake::Snake(int blockSize)
{
	size = blockSize;
	/*Set the size of the rectangle used to render the snake's segments*/
	segmentRectangle.setSize(sf::Vector2f(static_cast<float>(blockSize - 1), static_cast<float>(blockSize - 1)));
	/*Load initial values*/
	reset();
}


Snake::~Snake()
{
}

void Snake::changeDirection(Direction newDirection)
{
	/*Check if the change in direction is possible (new direction is not opposite to the current direction)*/
	if (currentDirection == Direction::Left && newDirection == Direction::Right) return;
	if (currentDirection == Direction::Right && newDirection == Direction::Left) return;
	if (currentDirection == Direction::Up && newDirection == Direction::Down) return;
	if (currentDirection == Direction::Down && newDirection == Direction::Up) return;

	/*Store future direction*/
	futureDirection = newDirection;
}

sf::Vector2i Snake::getHeadPosition() {
	/*Make sure snake is not empty and return the position of the first segment*/
	if (snakeSegmentPositions.empty()) return sf::Vector2i(0, 0);
	return snakeSegmentPositions[0];
}

bool Snake::headIntersectsFood(SnakeFood & food) {
	/*Head intersects a piece of food if the coordinates are equal*/
	return getHeadPosition() == food.getPosition();
}

void Snake::reset()
{
	/*Reset snake*/
	changeDirection(Direction::None);
	snakeSegmentPositions.clear();
	numberOfSegmentsToGrow = 0;
	/*Set initial position and size*/
	snakeSegmentPositions.push_back(sf::Vector2i(5, 5));
	growSegments(2);
}

void Snake::update()
{
	if (snakeSegmentPositions.empty()) return;

	/*Update the current direction*/
	currentDirection = futureDirection;

	/*Move each segment, except the head, one position along the snake*/
	auto lastSegmentPosition = *(snakeSegmentPositions.end() - 1);
	for (size_t index = snakeSegmentPositions.size() - 1; index > 0; index--) {
		snakeSegmentPositions[index] = snakeSegmentPositions[index - 1];
	}

	/*Move the snake's head according to the current direction*/
	switch (currentDirection) {
	case Direction::Down:
		snakeSegmentPositions[0].y++;
		break;
	case Direction::Up:
		snakeSegmentPositions[0].y--;
		break;
	case Direction::Left:
		snakeSegmentPositions[0].x--;
		break;
	case Direction::Right:
		snakeSegmentPositions[0].x++;
		break;
	default:
		break;
	}

	/*If the snake should grow longer, add a new segment at the previous position of the last segment*/
	if (numberOfSegmentsToGrow && currentDirection != Direction::None) {
		numberOfSegmentsToGrow--;
		snakeSegmentPositions.push_back(lastSegmentPosition);
	}
}

void Snake::cutTail(int segmentsToCut)
{
	/*Make sure there are no previously cut off segments stored*/
	cutSnakeSegmentPositions.clear();

	/*Remove the specified number of segments from the back of the snake*/
	while (segmentsToCut > 0 && !snakeSegmentPositions.empty()) {
		segmentsToCut--;
		
		/*Store the segments that were cut off*/
		cutSnakeSegmentPositions.push_back(snakeSegmentPositions.back());
		/*Remove the segments*/
		snakeSegmentPositions.pop_back();
	}
}

void Snake::growSegments(unsigned int numberOfSegments) {
	/*Increase the number of segments that need to be added*/
	numberOfSegmentsToGrow += numberOfSegments;
}

void Snake::render(sf::RenderWindow & renderWindow)
{
	if (snakeSegmentPositions.empty()) return;

	/*Draw the snake's body in white*/
	segmentRectangle.setFillColor(sf::Color::White);
	for (auto index = snakeSegmentPositions.begin() + 1; index != snakeSegmentPositions.end(); index++) {
		segmentRectangle.setPosition(sf::Vector2f(*index*size));
		renderWindow.draw(segmentRectangle);
	}

	/*Draw all segments that were cut off during this frame in red*/
	if (!cutSnakeSegmentPositions.empty()) {
		segmentRectangle.setFillColor(sf::Color::Red);
		for (auto index = cutSnakeSegmentPositions.begin() + 1; index != cutSnakeSegmentPositions.end(); index++) {
			segmentRectangle.setPosition(sf::Vector2f(*index*size));
			renderWindow.draw(segmentRectangle);
		}
		/*Delete these segments after they were rendereds*/
		cutSnakeSegmentPositions.clear();
	}

	/*Draw the snake's head in yellow*/
	segmentRectangle.setFillColor(sf::Color::Yellow);
	segmentRectangle.setPosition(sf::Vector2f(snakeSegmentPositions[0] * size));
	renderWindow.draw(segmentRectangle);
}

unsigned int Snake::checkIntersectionWithBody(sf::Vector2i position)
{
	if (snakeSegmentPositions.empty()) return 0;

	/*Check if any segment is at these coordinatesv (Starting at the first segment after the head)*/
	for (auto index = snakeSegmentPositions.begin() + 1; index != snakeSegmentPositions.end(); index++) {
		if (position.x == index->x && position.y == index->y) {
			/*Return the number of segments 'after' the intersection*/
			return(snakeSegmentPositions.end() - index);
		}
	}
	return 0;
}

bool Snake::snakeIntersectsFood(SnakeFood & food)
{
	/*Check if the coordinates of the food are on the snake's body or on the snake's head*/
	return (checkIntersectionWithBody(food.getPosition()) != 0) || (headIntersectsFood(food));
}

int Snake::checkForSelfIntersection()
{
	if (snakeSegmentPositions.empty()) return 0;

	/*Find out whether the snake's head collides with any of the other segments*/
	auto& head = snakeSegmentPositions[0];
	return checkIntersectionWithBody(head);	
}

size_t Snake::getLength() {
	/*Return the number of segments that define the snake*/
	return snakeSegmentPositions.size();
}
