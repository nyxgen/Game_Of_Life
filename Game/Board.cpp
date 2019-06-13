#include "Board.h"
using namespace std;


Board::Board(const numberU& tilesNumber)
{
	_position = positionU(0, 0);
	_board = make_shared<vector<vector<shared_ptr<Tile>>>>();
	_board->resize(tilesNumber.x);
	int k{ 0 };
	int l{ 0 };
	for (auto& i : (*_board))
	{
		i.resize(tilesNumber.y);
		for (auto& j : i)
		{
			j = make_shared<Tile>(positionU(_position.x + k * _size.x / tilesNumber.x, _position.y + l *_size.y / tilesNumber.y), sizeU(_size.x / tilesNumber.x, _size.y / tilesNumber.y), coordsU(k,l));
			++l;
		}
		++k;
		l = 0;
	}
}

Board::~Board()
{
}

const shared_ptr<Tile>& Board::operator()(const unsigned int & positionX, const unsigned int & positionY)
{
	if (positionX < (*_board).size() && positionY < (*_board)[positionX].size())
	{
		return (*_board)[positionX][positionY];
	}
	else
	{
		throw out_of_range("Tile not found");
	}
}

const shared_ptr<vector<vector<shared_ptr<Tile>>>>& Board::tiles()
{
	return _board;
}

const shared_ptr<Tile>& Board::tile(const unsigned int& positionX, const unsigned int& positionY)
{
	if (positionX < (*_board).size() && positionY < (*_board)[positionX].size())
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

positionU const& Board::position()
{
	return _position;
}

void Board::position(const positionU& position)
{
	_position = position;
	unsigned int k{ 0 };
    unsigned int l{ 0 };
	for (auto& i : (*_board))
	{
		for (auto& j : i)
		{
			j->position(positionU(static_cast<unsigned int>(position.x + k * _size.x / _board->size()), static_cast<unsigned int>(position.y + l * _size.y / i.size())));
			j->size(sizeU(static_cast<unsigned int>(_size.x / _board->size()), static_cast<unsigned int>(_size.y / i.size())));
			++l;
		}
		++k;
		l = 0;
	}
}

numberU Board::tilesCount()
{
	if (_board->size())
		return numberU(static_cast<unsigned int>(_board->size()), static_cast<unsigned int>((*_board)[0].size()));
	else
		return numberU(0,0);
}

void Board::size(const sizeU& boardSize)
{
	_size = boardSize;
	unsigned int k{ 0 };
	unsigned int l{ 0 };
	for (auto& i : (*_board))
	{
		for (auto& j : i)
		{
			j->position(positionU(static_cast<unsigned int>(_position.x + k * boardSize.x/ _board->size()), static_cast<unsigned int>(_position.y + l * boardSize.y / i.size())));
			j->size(sizeU(static_cast<unsigned int>(boardSize.x / _board->size()), static_cast<unsigned int>(boardSize.y / i.size())));
			++l;
		}
		++k;
		l = 0;
	}
}

const sizeU& Board::size()
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
	static sf::VertexArray va(sf::Quads, (_board->size()*(*_board)[0].size() + 2) * 4);
	if (_board->size() > 0 && (*_board)[0].size() > 0)
	{
		sizeU over = sizeU(15, 15);
		va[0].position = sf::Vector2f(_position - over);
		va[0].color = sf::Color(125, 125, 125);

		va[1].position = sf::Vector2f(static_cast<float>(_position.x + _size.x + over.x), static_cast<float>(_position.y - over.y));
		va[1].color = sf::Color(125, 125, 125);

		va[2].position = sf::Vector2f(_position + _size + over);
		va[2].color = sf::Color(125, 125, 125);

		va[3].position = sf::Vector2f(static_cast<float>(_position.x - over.x), static_cast<float>(_position.y + _size.y + over.y));
		va[3].color = sf::Color(125, 125, 125);

		va[4].position = sf::Vector2f(_position);
		va[4].color = sf::Color(125, 125, 125);

		va[5].position = sf::Vector2f(static_cast<float>(_position.x + _size.x), static_cast<float>(_position.y));
		va[5].color = sf::Color(125, 125, 125);

		va[6].position = sf::Vector2f(_position + _size);
		va[6].color = sf::Color(125, 125, 125);

		va[7].position = sf::Vector2f(static_cast<float>(_position.x), static_cast<float>(_position.y + _size.y));
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

