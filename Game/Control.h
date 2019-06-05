#pragma once
#include <SFML/Window.hpp>
class Control
{
	bool _lastStateLeft{ false };
	bool _lastStateRight{ false };
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
		t->checkMouseActions(sf::Mouse::Left, !_lastStateLeft);
		_lastStateLeft = true;
	}
	else
		_lastStateLeft = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		t->checkMouseActions(sf::Mouse::Right, !_lastStateRight);
		_lastStateRight = true;
	}
	else
		_lastStateRight = false;

}


