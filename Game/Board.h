#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace std;

class Board
{
	shared_ptr<vector<vector<shared_ptr<Tile>>>> _board = make_shared<vector<vector<shared_ptr<Tile>>>>();
	sf::Vector2u _position;
	sf::Vector2u _size;
public:
	Board() = delete;
	Board(const sf::Vector2u& tilesCount);
	~Board();

	const shared_ptr<vector<vector<shared_ptr<Tile>>>>& tiles();
	const shared_ptr<Tile>& tile(const int& positionX, const int& positionY);
	
	void alive(const int& positionX, const int& positionY, const bool& state);

	sf::Vector2u const& position();
	void position(const sf::Vector2u& position);

	const sf::Vector2u& tilesCount();

	void size(const sf::Vector2u& boardSize);
	const sf::Vector2u& size();

	void checkMouseActions(const sf::Mouse::Button& button, const bool & click);
	void targeted();

	void draw(const shared_ptr<sf::RenderWindow>& window);

	void clear();
};

