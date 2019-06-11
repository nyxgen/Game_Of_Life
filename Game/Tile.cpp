#include "Tile.h"

using namespace std;

Tile::Tile(const sizeU& size, const positionU& position, const coordsU& coords) : _alive(false)
{
	using namespace sf;

	_size = size;
	_position = position;
	_coords = coords;

	_vertex.resize(4);

	int j{ 0 };

	for(auto& i : _vertex)
	{
		i.position.x = (j == 0 || j == 3) ? static_cast<float>(_position.x) : static_cast<float>(_position.x + _size.x);
		i.position.y = (j == 0 || j == 1) ? static_cast<float>(_position.y) : static_cast<float>(_position.y + _size.y);
		i.color = DEAD;
		++j;
	}

	_border.width = static_cast<float>(_size.x);
	_border.height = static_cast<float>(_size.y);
	_border.left = static_cast<float>(_position.x);
	_border.top = static_cast<float>(_position.y);
}

Tile::~Tile()
{
}

const bool & Tile::alive()
{
	return _alive;
}

void Tile::addNeighbour(const shared_ptr<Tile>& neighbour)
{
	_neighbours.push_back(neighbour);
}

const vector<shared_ptr<Tile>>& Tile::neighbours()
{
	return _neighbours;
}

void Tile::clearNeighbours()
{
	_neighbours.clear();
}

void Tile::alive(const bool& state)
{
	using namespace sf;

	_alive = state;

	int j{ 0 };
	for(auto& i : _vertex)
	{
		i.color = _alive ? ALIVE : DEAD;
		++j;
	}
}

const positionU & Tile::position()
{
	return _position;
}

void Tile::position(const positionU& position)
{
	using namespace sf;

	_position = position;
	_border.left = static_cast<float>(_position.x);
	_border.top = static_cast<float>(_position.y);

	int j{ 0 };

	for(auto& i : _vertex)
	{
		i.position.x = (j == 0 || j == 3) ? static_cast<float>(_position.x) : static_cast<float>(_position.x + _size.x);
		i.position.y = (j == 0 || j == 1) ? static_cast<float>(_position.y) : static_cast<float>(_position.y + _size.y);
		i.color = _alive ?  ALIVE : DEAD;
		++j;
	}
}

const sizeU & Tile::size()
{
	return _size;
}

void Tile::size(const sizeU& size)
{
	using namespace sf;

	_size = size;
	_border.width = static_cast<float>(_size.x);
	_border.height = static_cast<float>(_size.y);

	int j{ 0 };

	for(auto& i : _vertex)
	{
		i.position.x = (j == 0 || j == 3) ? static_cast<float>(_position.x) : static_cast<float>(_position.x + _size.x);
		i.position.y = (j == 0 || j == 1) ? static_cast<float>(_position.y) : static_cast<float>(_position.y + _size.y);
		i.color = _alive ? ALIVE : DEAD;
		++j;
	}
}

bool Tile::targeted()
{
	using namespace sf;
	bool isTargeted = _border.contains(Vector2f(Mouse::getPosition()));
	if (isTargeted)
	{
		for (auto& i : _vertex)
			i.color = FOCUSED;
	}
	else
	{
		for (auto& i : _vertex)
			i.color = _alive ? ALIVE : DEAD;
	}
	return isTargeted;
}

void Tile::checkMouseActions(const sf::Mouse::Button& button, const bool & click)
{
	if (button == sf::Mouse::Left)
	{
		_alive = true;
		for (auto& i : _vertex)
			i.color = ALIVE;
		
	}
	if (button == sf::Mouse::Right)
	{
		_alive = false;
		for (auto& i : _vertex)
			i.color = DEAD;
	}
}

void Tile::coords(const coordsU & coords)
{
	_coords = coords;
}

const coordsU & Tile::coords()
{
	return _coords;
}

void Tile::draw(const shared_ptr<sf::RenderWindow>& window)
{
	static sf::VertexArray va(sf::Quads,4);
	int j{ 0 };

	for (auto& i : _vertex)
	{
		va[j] = i;
		++j;
	}
	window->draw(va);
}

const vector<sf::Vertex>& Tile::vertexes()
{
	return _vertex;
}


