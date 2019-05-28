#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

void Graphics::display()
{
	_window->display();
}

void Graphics::clear()
{
	_window->clear(sf::Color::Black);
}

const shared_ptr<sf::RenderWindow>& Graphics::window()
{
	return _window;
}

void Graphics::window(const shared_ptr<sf::RenderWindow>& window)
{
	_window = window;
}