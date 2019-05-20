#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#define ALIVE sf::Color::Blue
#define DEAD sf::Color::Black

using namespace std;

class Tile
{
	friend class Board;
	bool _alive;
	sf::Vector2u _position;
	sf::Vector2u _size;
	vector<sf::Vertex> _vertex;
	sf::FloatRect _border;
	void alive(const bool& state);
public:
	Tile() = delete;
	Tile(const sf::Vector2u& size, const sf::Vector2u& position);
	~Tile();

	bool const& alive();

	void position(const sf::Vector2u& position);
	sf::Vector2u const& position();

	void size(const sf::Vector2u& size);
	sf::Vector2u const& size();

	bool const& targeted();

	void setState();

	vector<sf::Vertex> const& vertexes();

};

