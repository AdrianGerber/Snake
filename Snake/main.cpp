#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main(int argc, char* argv[]) {
	/*Configure the game*/
	int screenXSize = 800;// 1920;
	int screenYSize = 400;// 1080;
	int blockSize = 20;
	sf::Time tickDuration = sf::milliseconds(50);
	Game game(screenXSize, screenYSize, blockSize, tickDuration);

	/*Gameloop*/
	while (game.isRunning()) {
		game.handleInput();
		game.update();
		game.render();
		game.measureLoopTime();
	}

	return 0;
}