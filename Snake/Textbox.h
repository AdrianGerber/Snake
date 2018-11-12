#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Textbox
{
public:
	Textbox();
	Textbox(int initialLinesVisible, int initialCharactersPerLine, int initialCharacterSize, sf::Vector2f initialPosition);

	~Textbox();

	/*Setup the textbox to display text*/
	void setup(int newLinesVisible, int newCharactersPerLine, int newCharacterSize, sf::Vector2f newPosition);
	/*Add text to the bottom of the box*/
	void addMessage(std::string str);
	/*Remove all stored lines of text*/
	void clear();

	/*Draw textbox inside the window*/
	void render(sf::RenderWindow& renderWindow);

private:
	/*Parameters defining the textbox*/
	unsigned int linesVisible;
	unsigned int charactersPerLine;
	unsigned int characterSize;
	sf::Vector2f position;
	
	/*Content of textbox*/
	std::vector<std::string> messages;
	bool contentChanged;

	/*Objects used for rendering*/
	sf::RectangleShape background;
	sf::Font font;
	sf::Text displayedText;
};

