#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#define ALIVE sf::Color::Blue
#define DEAD sf::Color::Green
#define FOCUSED sf::Color::Yellow

using namespace std;

class Tile
{
	friend class Board;
	bool _alive;
	sf::Vector2u _position;
	sf::Vector2u _coords;
	sf::Vector2u _size;
	vector<shared_ptr<Tile>> _neighbours;
	vector<sf::Vertex> _vertex;
	sf::FloatRect _border;
	void alive(const bool& state);
public:
	Tile() = delete;
	Tile(const sf::Vector2u& size, const sf::Vector2u& position, const sf::Vector2u& coords);
	~Tile();

	bool const& alive();

	void addNeighbour(const shared_ptr<Tile>& neighbour);
	const vector<shared_ptr<Tile>>& neighbours();
	void clearNeighbours();

	void position(const sf::Vector2u& position);
	sf::Vector2u const& position();

	void size(const sf::Vector2u& size);
	sf::Vector2u const& size();

	bool targeted();
	void checkMouseActions(const sf::Mouse::Button& button, const bool & click);

	void coords(const sf::Vector2u& coords);
	const sf::Vector2u& coords();

	void draw(const shared_ptr<sf::RenderWindow>& window);
	vector<sf::Vertex> const& vertexes();

};

