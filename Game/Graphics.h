#pragma once
#include <SFML/Graphics.hpp>

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
};

