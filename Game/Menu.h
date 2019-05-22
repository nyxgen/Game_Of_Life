#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Functions.h"

using namespace std;
class Button
{
	void changeColor(sf::Color color);
public:
	sf::Color _activeColor;
	sf::Color _inactiveColor;
	shared_ptr<Settings> _settings;
	sf::RectangleShape _button;
	sf::Texture _buttonTexture;
	sf::FloatRect _border;
	sf::Font _font;
	sf::Text _text;
	double _slider;
	string _name;
	string _type;
	int _fontSize;
	void(*_action)(shared_ptr<Settings>);
	Button(const sf::Vector2f& size, const sf::Vector2f& position, const shared_ptr<Settings>& settings, const string& texture);
	Button(const sf::Vector2f& size, const sf::Vector2f& position, const shared_ptr<Settings>& settings);
	Button();
	~Button();

	void borderInit();
	void changeTexture(const string& texturePath);

	void name(const string& name);
	const string& name();

	void type(const string& type);
	const string& type();

	const double& slider();

	void font(const string& fontPath);
	void fontSize(const int& fontSize);
	void text(const string& text);

	void size(const sf::Vector2f& size);
	void position(const sf::Vector2f& position);
	void settings(const shared_ptr<Settings>& settings);
	void textureColor(const sf::Color& color);
	void function(void(*)(shared_ptr<Settings>));

	void draw();
	bool isTargeted();
	const sf::Vector2i& cursorPosition();
};

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
	void showMenu();
	void checkMenu();
	void backgroundTexture(const string& path);
	void load(const string& path);
	
	~Menu();
};


