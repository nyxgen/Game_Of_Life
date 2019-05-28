#pragma once
#include <SFML/Window.hpp>
class Control
{
	bool lastStateLeft;
	bool lastStateRight;
public:
	Control();
	~Control();
	template<class T>
	void checkMouseActions(const T& t);
};

template<class T>
inline void Control::checkMouseActions(const T & t)
{
	t->targeted();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		lastStateLeft = true;
		t->checkMouseActions(sf::Mouse::Left, lastStateLeft);
	}
	else
		lastStateLeft = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		lastStateRight = true;
		t->checkMouseActions(sf::Mouse::Right, lastStateRight);
	}
	else
		lastStateRight = false;

}


