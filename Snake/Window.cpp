#include "Window.h"



Window::Window()
{
	setup("Title", sf::Vector2u(640, 480));
}

Window::Window(const std::string & initialWindowTitle, const sf::Vector2u & initialWindowSize)
{
	setup(initialWindowTitle, initialWindowSize);
}

void Window::beginDraw()
{
	/*Fill the window with the bsckground color*/
	renderWindow.clear(sf::Color::Black);
}

void Window::endDraw()
{
	/*Display the framebuffer onscreen*/
	renderWindow.display();
}

void Window::update()
{
	sf::Event event;
	/*Handle events*/
	while (renderWindow.pollEvent(event)) {
		/*Close window*/
		if (event.type == sf::Event::Closed) {
			bIsOpen = false;
		}
		/*Toggle fullscreen*/
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::F5) {
				toggleFullscreen();
			}
		}
	}
}

bool Window::isOpen(void)
{
	return bIsOpen;
}

bool Window::isFullscreen(void)
{
	return bIsFullscreen;
}

sf::Vector2u Window::getWindowSize()
{
	return windowSize;
}

void Window::setFramerateLimit(unsigned int limit)
{
	renderWindow.setFramerateLimit(limit);
}

void Window::toggleFullscreen()
{
	/*Reopen the window with new settings*/
	bIsFullscreen = !bIsFullscreen;
	destroy();
	create();
}

void Window::draw(sf::Drawable & drawable)
{
	/*Draw an object to the framebuffer*/
	renderWindow.draw(drawable);
}

void Window::setup(const std::string & newWindowTitle, const sf::Vector2u & newWindowSize)
{
	/*Initialize the window*/
	windowTitle = newWindowTitle;
	windowSize = newWindowSize;
	bIsFullscreen = false;
	bIsOpen = true;
	create();
}

void Window::destroy()
{
	renderWindow.close();
}

void Window::create()
{
	/*Create the window with the chosen size and style*/
	auto style = bIsFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	renderWindow.create({ windowSize.x, windowSize.y, 32 }, windowTitle, style);
}

Window::~Window()
{
	destroy();
}
