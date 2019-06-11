#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#define ALIVE sf::Color::Blue
#define DEAD sf::Color::Green
#define FOCUSED sf::Color::Yellow

using positionU = sf::Vector2u;
using coordsU = sf::Vector2u;
using sizeU = sf::Vector2u;

class Tile
{
	friend class Board;
	bool _alive;
	positionU _position;
	coordsU _coords;
	sizeU _size;
	std::vector<std::shared_ptr<Tile>> _neighbours;
	std::vector<sf::Vertex> _vertex;
	sf::FloatRect _border;
	void alive(const bool& state);
public:
	Tile() = delete;
	Tile(const sizeU& size, const positionU& position, const coordsU& coords);
	~Tile();

	bool const& alive();

	void addNeighbour(const std::shared_ptr<Tile>& neighbour);
	const std::vector<std::shared_ptr<Tile>>& neighbours();
	void clearNeighbours();

	void position(const positionU& position);
	const positionU & position();

	void size(const sizeU& size);
	const sizeU & size();

	bool targeted();
	void checkMouseActions(const sf::Mouse::Button& button, const bool & click);

	void coords(const coordsU& coords);
	const coordsU & coords();

	void draw(const std::shared_ptr<sf::RenderWindow>& window);
	std::vector<sf::Vertex> const& vertexes();

};

