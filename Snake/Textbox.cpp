#include "Textbox.h"



Textbox::Textbox()
{
	/*Create the textbox with default parameters*/
	setup(5, 200, 9, sf::Vector2f(0, 0));
}


Textbox::~Textbox()
{
	clear();
}

Textbox::Textbox(int initialLinesVisible, int initialCharactersPerLine, int initialCharacterSize, sf::Vector2f initialPosition)
{
	/*Setup the textbox*/
	setup(initialLinesVisible, initialCharactersPerLine, initialCharacterSize, initialPosition);
}

void Textbox::setup(int newLinesVisible, int newCharactersPerLine, int newCharacterSize, sf::Vector2f newPosition)
{
	/*Store configuration-values*/
	linesVisible = newLinesVisible;
	charactersPerLine = newCharactersPerLine;
	characterSize = newCharacterSize;
	position = newPosition;
	contentChanged = true;

	/*Load font*/
	font.loadFromFile("PIXELARIAL.TTF");
	
	/*Configure text*/
	displayedText.setFont(font);
	displayedText.setString("");
	displayedText.setCharacterSize(characterSize);
	displayedText.setFillColor(sf::Color::White);

	/*Offset the text from border of textbox*/
	sf::Vector2f offset(10.0f, 2.0f);
	displayedText.setPosition(position + offset);

	/*Configure the background*/
	float backgroundSizeX = charactersPerLine * characterSize + 2 * offset.x;
	float backgroundSizeY = linesVisible * (font.getLineSpacing(characterSize) + 2 * offset.y);
	background.setSize(sf::Vector2f(backgroundSizeX, backgroundSizeY));
	background.setFillColor(sf::Color(90, 90, 90, 90));
	background.setPosition(position);
}

void Textbox::addMessage(std::string str)
{
	/*Make sure the text will be updated before rendering*/
	contentChanged = true;
	
	/*Erase old messages that will not fit on the screen*/
	if (messages.size() >= linesVisible) {
		messages.erase(messages.begin());
	}

	/*If the text fits on one line, store it as one line*/
	if (str.length() <= charactersPerLine) {
		messages.push_back(str);
		return;
	}
	
	/*The message doesn't fit on one line --> split it up */
	messages.push_back(str.substr(0, charactersPerLine));
	addMessage(str.substr(charactersPerLine));
}

void Textbox::clear()
{
	/*Remove all messages from the container*/
	messages.clear();
	contentChanged = true;
}

void Textbox::render(sf::RenderWindow & renderWindow)
{
	/*Recalculate the text's content if the strings inside the container changed*/
	if (contentChanged) {
		contentChanged = false;

		/*Add all lines to the text*/
		std::string textBoxContent = "";
		for (auto line : messages) {
			textBoxContent += line;
			textBoxContent += "\n";
		}
		
		displayedText.setString(textBoxContent);
	}

	/*Render background and text*/
	if (!displayedText.getString().isEmpty()) {
		renderWindow.draw(background);
		renderWindow.draw(displayedText);
	}
}
