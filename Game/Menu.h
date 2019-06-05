#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Button.h"
#include "Functions.h"

using namespace std;

class Menu
{
	sf::RectangleShape _background;
	sf::Texture _backgroundTexture;
	shared_ptr<Settings> _settings;
public:
	Menu(const shared_ptr<Settings>& settings, const int& buttonCount);
	Menu(const shared_ptr<Settings>& settings);
	vector<shared_ptr<Button>> buttons;
	const shared_ptr<Button>& button(const string& name);
	void draw(const shared_ptr<sf::RenderWindow>& window);
	void targeted();
	void checkMouseActions(const sf::Mouse::Button& button, const bool click);
	void backgroundTexture(const string& path);
	void loadFromFile(const string& path);
	
	~Menu();
};


