#pragma once
#include <SFML/Graphics.hpp>
#include <boost/spirit/home/support/container.hpp>
#include "Board.h"

using namespace std;
class Graphics
{
	shared_ptr<sf::RenderWindow> _window;
	sf::ContextSettings _settings;
public:
	Graphics();
	~Graphics();
	void display();
	void clear();
	const shared_ptr<sf::RenderWindow>& window();
	void window(const shared_ptr<sf::RenderWindow>& window);
	template<class T>
	void draw(const T& t);
};

template<class T>
inline void Graphics::draw(const T & t)
{
	t->draw(_window);
}