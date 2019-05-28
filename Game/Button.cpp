#include "Button.h"

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

bool Button::targeted()
{
	bool targeted = _border.contains(sf::Vector2f(sf::Mouse::getPosition()));
	if (targeted)
	{
		changeColor(_activeColor);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
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

void Button::draw(const shared_ptr<sf::RenderWindow>& window)
{
	static sf::RectangleShape slider;
	static int sliderWidth{ 4 };
	window->draw(_button);
	window->draw(_text);
	if (_type == "slider")
	{
		slider.setPosition(sf::Vector2f(_border.left + _slider * (_border.width - sliderWidth), _border.top));
		slider.setSize(sf::Vector2f(sliderWidth, _border.height));
		slider.setFillColor(sf::Color::White);
		slider.setOutlineThickness(1);
		slider.setOutlineColor(sf::Color::Black);
		window->draw(slider);
	}
}
