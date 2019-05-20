#include "Graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{
}

void Graphics::display()
{
	window->display();
}

void Graphics::clear()
{
	window->clear(sf::Color::Black);
}
shared_ptr<sf::RenderWindow> Graphics::getWindow()
{
	return window;
}

void Graphics::setWindow(shared_ptr<sf::RenderWindow> window)
{
	this->window = window;
}