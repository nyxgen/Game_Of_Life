#include "Menu.h"
using namespace std;

void Button::changeColor(sf::Color color)
{
	_button.setFillColor(color);
}

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const shared_ptr<Settings>& settings, const string& texture)
{
	_settings = settings;
	_buttonTexture.loadFromFile(texture);
	_button.setPosition(position);
	_button.setSize(size);
	_button.setTexture(&_buttonTexture);
	_border.left = _button.getPosition().x;
	_border.top = _button.getPosition().y;
	_border.width = _button.getSize().x;
	_border.height = _button.getSize().y;
	_slider = 0;
}
Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const shared_ptr<Settings>& settings)
{
	_settings = settings;
	_button.setPosition(position);
	_button.setSize(size);
	_border.left = _button.getPosition().x;
	_border.top = _button.getPosition().y;
	_border.width = _button.getSize().x;
	_border.height = _button.getSize().y;
	_slider = 0;
}
void Button::borderInit()
{
	_border.left = _button.getPosition().x;
	_border.top = _button.getPosition().y;
	_border.width = _button.getSize().x;
	_border.height = _button.getSize().y;
}

Button::Button()
{
	_slider = 0;
}
Button::~Button()
{
}

void Button::function(void(*func)(shared_ptr<Settings>))
{
	_action = func;
}

bool Button::isTargeted()
{
	bool targeted = _border.contains(sf::Vector2f(sf::Mouse::getPosition()));
	if (targeted)
	{
		changeColor(_activeColor);
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cursorPosition();
	}
	else
	{
		changeColor(_inactiveColor);
	}
	return targeted;
}
const sf::Vector2i& Button::cursorPosition()
{
	sf::Vector2i currentPosition = sf::Mouse::getPosition() - sf::Vector2i(_border.left, _border.top);
	_slider = 1.0* currentPosition.x / (0.95 * _border.width);
	if (_slider < 0)
		_slider = 0;
	if (_slider > 1)
		_slider = 1;
	return currentPosition;
}
void Button::changeTexture(const string& texture)
{
	_buttonTexture.loadFromFile(texture);
	_button.setTexture(&_buttonTexture);
}

void Button::name(const string& name)
{
	_name = name;
}

const string& Button::name()
{
	return _name;
}

void Button::type(const string& type)
{
	_type = type;
}

const string& Button::type()
{
	return _type;
}

const double& Button::slider()
{
	return _slider;
}

void Button::font(const string& fontPath)
{
	_font.loadFromFile(fontPath);
	_text.setFont(_font);
}

void Button::fontSize(const int& fontSize)
{
	_text.setCharacterSize(fontSize);
}

void Button::text(const string& text)
{
	_text.setString(text);
	sf::FloatRect textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	sf::FloatRect buttonRect = _button.getLocalBounds();
	sf::Vector2f center(buttonRect.left + buttonRect.width / 2.0f,
		buttonRect.top + buttonRect.height / 2.0f);
	_text.setPosition(_button.getPosition() + center);
}

void Button::size(const sf::Vector2f& size)
{
	_button.setSize(size);
}

void Button::position(const sf::Vector2f& position)
{
	sf::FloatRect buttonRect = _button.getLocalBounds();
	_button.setOrigin(buttonRect.left + buttonRect.width / 2.0f,
		buttonRect.top + buttonRect.height / 2.0f);
	_button.setPosition(position);
}

void Button::settings(const shared_ptr<Settings>& settings)
{
	_settings = settings;
}

void Button::textureColor(const sf::Color& color)
{
	_button.setFillColor(color);
}

void Button::draw()
{
	_settings->window()->draw(_button);
	_settings->window()->draw(_text);
	if (_type == "slider")
	{
		sf::RectangleShape slider;
		int sliderWidth = 4;
		slider.setPosition(sf::Vector2f(_border.left + this->_slider * (_border.width-sliderWidth), _border.top));
		slider.setSize(sf::Vector2f(sliderWidth, _border.height));
		slider.setFillColor(sf::Color::White);
		slider.setOutlineThickness(1);
		slider.setOutlineColor(sf::Color::Black);
		_settings->window()->draw(slider);
	}
	
}

const shared_ptr<Button>& Menu::button(const string& name)
{
	for (auto& i : buttons)
	{
		if (i->name() == name)
			return i;
	}
	throw exception("Nie znaleziono");
}

void Menu::showMenu()
{
	_settings->window()->clear(sf::Color(0, 0, 0, 255));
	_settings->window()->draw(_background);
	for(auto& i : buttons)
	{
		i->draw();
	}
}

void Menu::checkMenu()
{
	for (auto& i : buttons)
	{
		if (i->isTargeted() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				i->_action(_settings);
		}
	}
}

void Menu::backgroundTexture(const string& texture)
{
	_backgroundTexture.loadFromFile(texture);
	_background.setTexture(&_backgroundTexture);
}

Menu::Menu(const shared_ptr<Settings>& options, const unsigned int& buttonCount)
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
						button->function(getFunction(function));
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

