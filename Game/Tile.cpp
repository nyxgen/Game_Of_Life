#include "Tile.h"


Tile::Tile(const sf::Vector2u& size, const sf::Vector2u& position) : _alive(false)
{
	using namespace sf;

	_size = size;
	_position = position;

	_vertex.resize(4);

	int j{ 0 };

	for (auto& v : _vertex)
	{
		v.position.x = (j == 0 || j == 3) ? _position.x : (_position.x + _size.x);
		v.position.y = (j == 0 || j == 1) ? _position.y : (_position.y + _size.y);
		v.color = DEAD;
		++j;
	}

	_border.width = _size.x;
	_border.height = _size.y;
	_border.left = _position.x;
	_border.top = _position.y;
}

Tile::~Tile()
{
}

bool const& Tile::alive()
{
	return _alive;
}

void Tile::alive(const bool& state)
{
	using namespace sf;

	this->_alive = state;

	for (auto& v : _vertex)
	{
		v.color = _alive ? ALIVE : DEAD;
	}
}

sf::Vector2u const& Tile::position()
{
	return _position;
}

void Tile::position(const sf::Vector2u& position)
{
	using namespace sf;

	_position = position;
	_border.left = _position.x;
	_border.top = _position.y;

	int j{ 0 };

	for (auto& v : _vertex)
	{
		v.position.x = (j == 0 || j == 3) ? _position.x : (_position.x + _size.x);
		v.position.y = (j == 0 || j == 1) ? _position.y : (_position.y + _size.y);
		v.color = _alive ?  ALIVE : DEAD;
		++j;
	}
}

sf::Vector2u const& Tile::size()
{
	return _size;
}

void Tile::size(const sf::Vector2u& size)
{
	using namespace sf;

	_size = size;
	_border.width = _size.x;
	_border.height = _size.y;

	int j{ 0 };

	for (auto& v : _vertex)
	{
		v.position.x = (j == 0 || j == 3) ? _position.x : (_position.x + _size.x);
		v.position.y = (j == 0 || j == 1) ? _position.y : (_position.y + _size.y);
		int i = _position.y + _size.y;
		v.color = _alive ? ALIVE : DEAD;
		++j;
	}
}

bool const& Tile::targeted()
{
	using namespace sf;
	return _border.contains(Vector2f(Mouse::getPosition()));
}

void Tile::setState()
{
	using namespace sf;
	if (targeted())
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			alive(true);
		}
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			alive(false);
		}
	}
}

vector<sf::Vertex> const& Tile::vertexes()
{
	return _vertex;
}

