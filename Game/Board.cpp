#include "Board.h"

Board::Board(const sf::Vector2u& size)
{
	_position = sf::Vector2u(0, 0);
	_board->resize(size.x);
	int k{ 0 };
	int l{ 0 };
	for (auto& i : (*_board))
	{
		i.resize(size.y);
		for (auto& j : i)
		{
			j = make_shared<Tile>(sf::Vector2u(_position.x + k * _boardSize.x / size.x, _position.y + l *_boardSize.y / size.y), sf::Vector2u(_boardSize.x / size.x, _boardSize.y / size.y));
			++l;
		}
		++k;
		l = 0;
	}
}

Board::~Board()
{
}

const shared_ptr<Tile>& Board::tile(const int& positionX, const int& positionY)
{
	if (positionX >= 0 && positionY >= 0 && positionX < (*_board).size() && positionY < (*_board)[positionX].size())
	{
		return (*_board)[positionX][positionY];
	}
	else
	{
		throw out_of_range("Tile not found");
	}
}

void Board::alive(const int& positionX, const int& positionY, const bool& state)
{
	if (state)
	{
		_aliveCells->push_back(pair<int, int>(positionX, positionY));
		sort(_aliveCells->begin(), _aliveCells->end());
		auto last = unique(_aliveCells->begin(), _aliveCells->end());
		_aliveCells->erase(last, _aliveCells->end());
		(*_board)[positionX][positionY]->alive(true);
	}
	else
	{
		bool found = false;
		pair<int, int> toFind(positionX, positionY);
		int position = 0;
		for (int i = 0; i < _aliveCells->size() && !found; i++)
		{
			if ((*_aliveCells)[i] == toFind)
			{
				position = i;
				found = true;
			}

		}
		if (found)
			_aliveCells->erase(_aliveCells->begin() + position);

		(*_board)[positionX][positionY]->alive(false);
	}
}

sf::Vector2u const& Board::position()
{
	return _position;
}

void Board::position(const sf::Vector2u& position)
{
	_position = position;
	int k{ 0 };
	int l{ 0 };
	for (auto& i : (*_board))
	{
		for (auto& j : i)
		{
			j->position(sf::Vector2u(position.x + k * _boardSize.x / _board->size(), position.y + l * _boardSize.y / i.size()));
			j->size(sf::Vector2u(_boardSize.x / _board->size(), _boardSize.y / i.size()));
			++l;
		}
		++k;
		l = 0;
	}
}

const sf::Vector2u& Board::size()
{
	if (_board->size())
		return sf::Vector2u(_board->size(), (*_board)[0].size());
	else
		return sf::Vector2u(0,0);
}

void Board::boardSize(const sf::Vector2u& boardSize)
{
	_boardSize = boardSize;
	int k{ 0 };
	int l{ 0 };
	for (auto& i : (*_board))
	{
		for (auto& j : i)
		{
			j->position(sf::Vector2u(_position.x + k * boardSize.x/ _board->size(), _position.y + l * boardSize.y / i.size()));
			j->size(sf::Vector2u(boardSize.x / _board->size(), boardSize.y / i.size()));
			++l;
		}
		++k;
		l = 0;
	}
}

const sf::Vector2u& Board::boardSize()
{
	return _boardSize;
}

const shared_ptr<vector<pair<int, int>>>& Board::aliveCells()
{
	return _aliveCells;
}

void Board::clear()
{
	for (auto& i : (*_board))
	{
		for (auto& j : i)
		{
			j->alive(false);
		}
	}
}