#include "Board.h"

Board::Board(const sf::Vector2u& tilesCount)
{
	_position = sf::Vector2u(0, 0);
	_board->resize(tilesCount.x);
	int k{ 0 };
	int l{ 0 };
	for (auto& i : (*_board))
	{
		i.resize(tilesCount.y);
		for (auto& j : i)
		{
			j = make_shared<Tile>(sf::Vector2u(_position.x + k * _size.x / tilesCount.x, _position.y + l *_size.y / tilesCount.y), sf::Vector2u(_size.x / tilesCount.x, _size.y / tilesCount.y), sf::Vector2u(k,l));
			++l;
		}
		++k;
		l = 0;
	}
}

Board::~Board()
{
}

const shared_ptr<vector<vector<shared_ptr<Tile>>>>& Board::tiles()
{
	return _board;
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
	(*_board)[positionX][positionY]->alive(state);
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
			j->position(sf::Vector2u(position.x + k * _size.x / _board->size(), position.y + l * _size.y / i.size()));
			j->size(sf::Vector2u(_size.x / _board->size(), _size.y / i.size()));
			++l;
		}
		++k;
		l = 0;
	}
}

const sf::Vector2u& Board::tilesCount()
{
	if (_board->size())
		return sf::Vector2u(_board->size(), (*_board)[0].size());
	else
		return sf::Vector2u(0,0);
}

void Board::size(const sf::Vector2u& boardSize)
{
	_size = boardSize;
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

const sf::Vector2u& Board::size()
{
	return _size;
}

void Board::checkMouseActions(const sf::Mouse::Button& button, const bool & click)
{
	for (auto& i : (*_board))
	{
		for (auto& j : i)
		{
			if (j->targeted())
			{
				j->checkMouseActions(button, click);
			}
		}
	}
}

void Board::targeted()
{
	for (auto& i : (*_board))
	{
		for (auto& j : i)
		{
			j->targeted();
		}
	}
}

void Board::draw(const shared_ptr<sf::RenderWindow>& window)
{
	static sf::VertexArray va(sf::Quads,(_board->size()*(*_board)[0].size()+2)*4);
	if (_board->size() > 0 && (*_board)[0].size() > 0)
	{
		sf::Vector2u over = sf::Vector2u(15, 15);
		va[0].position = sf::Vector2f(_position - over);
		va[0].color = sf::Color(125, 125, 125);

		va[1].position = sf::Vector2f(_position.x + _size.x + over.x, _position.y - over.y);
		va[1].color = sf::Color(125, 125, 125);

		va[2].position = sf::Vector2f(_position + _size + over);
		va[2].color = sf::Color(125, 125, 125);

		va[3].position = sf::Vector2f(_position.x - over.x, _position.y + _size.y + over.y);
		va[3].color = sf::Color(125, 125, 125);

		va[4].position = sf::Vector2f(_position);
		va[4].color = sf::Color(125, 125, 125);

		va[5].position = sf::Vector2f(_position.x + _size.x, _position.y);
		va[5].color = sf::Color(125, 125, 125);

		va[6].position = sf::Vector2f(_position + _size);
		va[6].color = sf::Color(125, 125, 125);

		va[7].position = sf::Vector2f(_position.x, _position.y + _size.y);
		va[7].color = sf::Color(125, 125, 125);
	}

	int l{ 0 };
	for (auto& i : (*_board))
	{
		for (auto& j : i)
		{
			for (auto& k : j->_vertex)
			{
				va[8 + l] = k;
				++l;
			}
		}
	}
	window->draw(va);
	
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