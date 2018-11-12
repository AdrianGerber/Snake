#include "Game.h"
#include <string>


Game::Game(int initialScreenSizeX, int initialScreenSizeY, int initialBlockSize, sf::Time tickDuration) : gameWindow("Snake", sf::Vector2u(initialScreenSizeX, initialScreenSizeY)){
	/*Setting up the window*/
	windowSize = sf::Vector2i(gameWindow.getWindowSize());
	gameWindow.setFramerateLimit(30);
	/*Store desired duration between two updates of the playworld*/
	tickTime = tickDuration;
	/*Seed prng*/
	srand(static_cast<unsigned int>(time(0)));
	
	/*Size of 1 'block'*/
	blockSize = initialBlockSize;
	/*Setup snake and snakefood*/
	sf::Vector2u playFieldSize = gameWindow.getWindowSize() / static_cast<unsigned int>(blockSize);
	snake = Snake(blockSize);
	snakeFood = SnakeFood(blockSize, sf::Vector2i(static_cast<int>(playFieldSize.x - 2),static_cast<int>(playFieldSize.y - 2)), sf::Vector2i(1, 1));
	/*Define color and size of the four walls*/
	for (auto& border : gameBorders) {
		border.setBlockSize(blockSize);
		border.setColor(sf::Color::White);
	}
	/*Position the walls at the border of the screen*/
	gameBorders[0].setPosition(sf::Vector2i(0, 0));
	gameBorders[0].setSize(sf::Vector2i(1, playFieldSize.y));
	gameBorders[1].setPosition(sf::Vector2i(0, 0));
	gameBorders[1].setSize(sf::Vector2i(playFieldSize.x, 1));
	gameBorders[2].setPosition(sf::Vector2i(playFieldSize.x - 1, 0));
	gameBorders[2].setSize(sf::Vector2i(1, playFieldSize.y));
	gameBorders[3].setPosition(sf::Vector2i(0, playFieldSize.y - 1));
	gameBorders[3].setSize(sf::Vector2i(playFieldSize.x, 1));

	/*Setup textbox to display messages to the player*/
	textbox.setup(7, 20, 15, sf::Vector2f(0, 0));

	/*Let the game begin...*/
	restartGame();
}


Game::~Game()
{
}

void Game::handleInput()
{
	/*Change the snake's direction if the corresponding key is pressed*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) snake.changeDirection(Direction::Left);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) snake.changeDirection(Direction::Down);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) snake.changeDirection(Direction::Right);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) snake.changeDirection(Direction::Up);
}

void Game::update()
{
	/*Move the simulation forward a timestep until it is up to date*/
	while (totalLoopTime - lastUpdateTime > tickTime) {
		lastUpdateTime += tickTime;

		/*Let the window react to events such as a click on 'close'*/
		gameWindow.update();

		/*Let the snake 'think' and move*/
		snake.update();

		/*Check if the snake can eat a piece of food*/
		if (snake.headIntersectsFood(snakeFood)) {
			/*Extend the size of the snake*/
			snake.growSegments(1);

			/*Update score*/
			score += 10;
			printScore();

			/*Find a new position for the snakefood that's not already inside the snake*/
			do {
				snakeFood.randomizePosition();
			} while (snake.snakeIntersectsFood(snakeFood) );
		}

		/*Check if the snake collides with any border --> game over!*/
		for (auto& border : gameBorders) {
			if (border.checkIntersection(snake.getHeadPosition())) {
				gameOver();
			}
		}

		/*Check if the snake intersects itself*/
		auto intersectionSegment = snake.checkForSelfIntersection();
		if (intersectionSegment) {
			/*Make the snakehead 'cut' off all segments behind the intersection*/
			snake.cutTail(intersectionSegment);
			/*Remove a live for each collision of the snake with itself*/
			lives--;
			/*No lives left --> game over!*/
			if (lives == 0) {
				gameOver();
			}
			/*If game continues, display the remaining number of lives*/
			else {
				textbox.addMessage(std::string("Lives Left: ") + std::to_string(lives));
			}
		}
	}
}

void Game::render()
{
	/*Start a new frame*/
	gameWindow.beginDraw();

	auto& renderWindow = gameWindow.getRenderWindow();

	/*Let each object render itself according to it's current state*/
	for (auto& border : gameBorders) {
		border.render(renderWindow);
	}
	snakeFood.render(renderWindow);
	snake.render(renderWindow);
	textbox.render(renderWindow);

	/*Complete the frame*/
	gameWindow.endDraw();
}

void Game::measureLoopTime()
{
	/*Record timestamp of when the last iteration of the gameloop was completed*/
	totalLoopTime = loopClock.getElapsedTime();
}


bool Game::isRunning()
{
	/*Return true if the game should keep running*/
	return gameWindow.isOpen();
}

void Game::restartGame()
{
	/*Reset score and prepare for new game*/
	score = 0;
	lives = 3;
	snake.reset();
	snakeFood.randomizePosition();
	/*Tell the player about the restart*/
	textbox.addMessage("New Game!");
}

void Game::gameOver()
{
	/*Display "Game Over!" and output the Score reached*/
	textbox.addMessage(" ");
	textbox.addMessage("Game Over!");
	textbox.addMessage(std::string("Final Score: ") + std::to_string(score));
	textbox.addMessage(" ");

	/*Start a new game*/
	restartGame();
}

void Game::printScore()
{
	/*Print the current score into the textbox*/
	textbox.addMessage(std::string("Score: ") + std::to_string(score));
}
