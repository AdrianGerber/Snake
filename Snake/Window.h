#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Window
{
public:
	Window();
	~Window();
	Window(const std::string& initialWindowTitle, const sf::Vector2u& initialWindowSize);

	/*Methods used for rendering a frame*/
	void beginDraw();
	void draw(sf::Drawable& drawable);
	void endDraw();

	/*React to events*/
	void update();

	/*Retrieve information about the window*/
	bool isOpen();
	bool isFullscreen();
	sf::Vector2u getWindowSize();
	
	/*Get the renderwindow*/
	inline sf::RenderWindow& getRenderWindow() {
		return renderWindow;
	}
	
	/*Set limit for framerate*/
	void setFramerateLimit(unsigned int limit);
	/*Switch between windowed and fullscreen*/
	void toggleFullscreen();
	

	

private:
	/*Opening and closing the window*/
	void setup(const std::string& newWindowTitle, const sf::Vector2u& newWindowSize);
	void destroy(void);
	void create(void);

	/*Information that defines the window*/
	sf::RenderWindow renderWindow;
	sf::Vector2u windowSize;
	std::string windowTitle;
	bool bIsOpen;
	bool bIsFullscreen;
};

