#include "Menu.h"
using namespace std;

const shared_ptr<Button>& Menu::button(const string& name)
{
	for (auto& i : buttons)
	{
		if (i->name() == name)
			return i;
	}
	throw exception("Nie znaleziono");
}

void Menu::draw(const shared_ptr<sf::RenderWindow>& window)
{
	window->draw(_background);
	for (auto& i : buttons)
	{
		i->draw(window);
	}
}

void Menu::targeted()
{
	for (auto& i : buttons)
	{
		i->targeted();
	}
}

void Menu::checkMouseActions(const sf::Mouse::Button& button, const bool & click)
{
	for (auto& i : buttons)
	{
		if (button == sf::Mouse::Left && click && i->targeted())
		{
			i->_action(i->_settings);
		}
	}
}

void Menu::backgroundTexture(const string& texture)
{
	_backgroundTexture.loadFromFile(texture);
	_background.setTexture(&_backgroundTexture);
}

Menu::Menu(const shared_ptr<Settings>& options, const int& buttonCount)
{
	_settings = options;
	sf::Vector2f size = sf::Vector2f(_settings->window()->getSize());
	_background.setSize(size);
	for (int i = 0; i < buttonCount; ++i)
	{
		buttons.push_back(make_shared<Button>(sf::Vector2f(200, 100), sf::Vector2f(800, 200 + i * 150), _settings));
	}
}

Menu::Menu(const shared_ptr<Settings>& settings)
{
	_settings = settings;
	sf::Vector2f size = sf::Vector2f(settings->window()->getSize());
	_background.setSize(size);
}

void Menu::load(const string& path)
{
	fstream file;
	file.open(path, ios::in);
	if (file.good() == false) return;

	while (!file.eof())
	{
		string word2;
		for (file >> word2; file.good(); file >> word2)
		{
			if (word2 == "Button")
			{
				shared_ptr<Button> button = make_shared<Button>();
				button->settings(_settings);
				string word3;
				int x, y, fontSize, sizeX, sizeY, R, G, B, alfa;
				string font, text, texture, function, name, type;
				for (file >> word3; word3 != "}"; file >> word3)
				{
					if (word3 == "Type")
					{
						file >> type;
						button->type(type);
					}
					if (word3 == "Name")
					{
						file >> name;
						button->name(name);
					}
					if (word3 == "Position")
					{
						file >> x;
						file >> y;
						button->position(sf::Vector2f(x, y));
					}
					else if (word3 == "Font")
					{
						file >> font;
						button->font(font);
					}
					else if (word3 == "FontSize")
					{
						file >> fontSize;
						button->fontSize(fontSize);
					}
					else if (word3 == "Text")
					{
						file >> text;
						button->text(text);
					}
					else if (word3 == "Texture")
					{
						file >> texture;
						button->changeTexture(texture);
					}
					else if (word3 == "ActiveColor")
					{
						file >> R >> G >> B >> alfa;
						button->_activeColor = sf::Color(sf::Color(R, G, B, alfa));
					}
					else if (word3 == "InactiveColor")
					{
						file >> R >> G >> B >> alfa;
						button->_inactiveColor = sf::Color(sf::Color(R, G, B, alfa));
					}
					else if (word3 == "Size")
					{
						file >> sizeX >> sizeY;
						button->size(sf::Vector2f(sizeX, sizeY));
					}
					else if (word3 == "Function")
					{
						file >> function;
						button->function(Functions::getFunction(function));
					}
				}
				button->borderInit();
				buttons.push_back(button);
			}
			else if (word2 == "Background")
			{
				string texture, word3;
				for (file >> word3; word3 != "}"; file >> word3)
				{
					if (word3 == "Path")
					{
						file >> texture;
						backgroundTexture(texture);
					}
				}
			}
		}
	}
}

Menu::~Menu()
{
	buttons.clear();
}

