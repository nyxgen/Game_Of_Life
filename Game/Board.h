#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace std;

class Board
{
	shared_ptr<vector<vector<shared_ptr<Tile>>>> _board = make_shared<vector<vector<shared_ptr<Tile>>>>();
	shared_ptr<vector<pair<int,int>>> _aliveCells = make_shared<vector<pair<int,int>>>();
	sf::Vector2u _position;
	sf::Vector2u _boardSize;
public:
	Board() = delete;
	Board(const sf::Vector2u& size);
	~Board();

	const shared_ptr<Tile>& tile(const int& positionX, const int& positionY);
	
	void alive(const int& positionX, const int& positionY, const bool& state);

	sf::Vector2u const& position();
	void position(const sf::Vector2u& position);

	const sf::Vector2u& size();

	void boardSize(const sf::Vector2u& boardSize);
	const sf::Vector2u& boardSize();

	const shared_ptr<vector<pair<int, int>>>& aliveCells();

	void clear();
};

