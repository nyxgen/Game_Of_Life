#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"

using numberU = sf::Vector2u;

class Board
{
	std::shared_ptr<std::vector<std::vector<std::shared_ptr<Tile>>>> _board;
	sf::VertexArray _vertexArray;
	positionU _position;
	sizeU _size;
public:
	Board() = delete;
	Board(const numberU& tilesCount);
	~Board();

	const std::shared_ptr<Tile>& operator()(const unsigned int& positionX, const unsigned int& positionY);

	const std::shared_ptr<std::vector<std::vector<std::shared_ptr<Tile>>>>& tiles();
	const std::shared_ptr<Tile>& tile(const unsigned int& positionX, const unsigned int& positionY);
	
	void alive(const int& positionX, const int& positionY, const bool& state);

	positionU const& position();
	void position(const positionU& position);

	numberU tilesCount();

	void size(const sizeU& boardSize);
	const sizeU& size();

	void checkMouseActions(const sf::Mouse::Button& button, const bool & click);
	void targeted();

	void draw(const std::shared_ptr<sf::RenderWindow>& window);

	void clear();
};

