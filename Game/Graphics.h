#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
class Graphics
{
	shared_ptr<sf::RenderWindow> window;
	sf::ContextSettings settings;
public:
	Graphics();
	~Graphics();
	void display();
	void clear();
	shared_ptr<sf::RenderWindow> getWindow();
	void setWindow(shared_ptr<sf::RenderWindow> window);
};

