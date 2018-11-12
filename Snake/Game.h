

#pragma once
#include "Window.h"
#include "Snake.h"
#include "SnakeFood.h"
#include "Wall.h"
#include <array>
#include "Textbox.h"

class Game
{
public:
	Game(int initialScreenSizeX=1920, int initialScreenSizeY=1080, int initialBlockSize = 20, sf::Time tickDuration = sf::milliseconds(100));
	~Game();

	/*Handle keyboard controls*/
	void handleInput();
	/*Update world*/
	void update();
	/*Draw a frame of the game*/
	void render();
	/*Create timestamp of when last loop was completed*/
	void measureLoopTime();

	/*Is the game running?*/
	bool isRunning();
	/*Reset state of the game and restart simulation*/
	void restartGame();

private:
	/*React to end of game*/
	void gameOver();
	/*Display current score inside textbox*/
	void printScore();

	/*Variables to store the world*/
	Snake snake;
	SnakeFood snakeFood;
	Window gameWindow;
	std::array<Wall, 4> gameBorders;
	
	/*Variables for display of information to the player*/
	unsigned int lives;
	unsigned int score;
	Textbox textbox;

	/*Information needed to run the simulation*/
	sf::Vector2i windowSize;
	int blockSize;
	sf::Clock loopClock;
	sf::Time lastUpdateTime;
	sf::Time totalLoopTime;
	sf::Time tickTime;
};

