#include "Board.h"

Board::Board(int& sizeX, int& sizeY):position(pair<int, int>(0,0))
{
	board->resize(sizeX);
	for (int i = 0; i < sizeX; i++)
	{
		(*board)[i].resize(sizeY);
		for (int j = 0; j < sizeY; j++)
		{
			(*board)[i][j] = make_shared<Tile>();
		}
	}
}

Board::Board(int && sizeX, int && sizeY):position(pair<int, int>(0, 0))
{
	board->resize(sizeX);
	for (int i = 0; i < sizeX; i++)
	{
		(*board)[i].resize(sizeY);
		for (int j = 0; j < sizeY; j++)
		{
			(*board)[i][j] = make_shared<Tile>();
		}
	}
}

Board::~Board()
{
}

shared_ptr<Tile> Board::getTile(int positionX, int positionY)
{
	if (positionX >= 0 && positionY >= 0 && positionX < (*board).size() && positionY < (*board)[positionX].size())
	{
		return (*board)[positionX][positionY];
	}
	else
	{
		throw out_of_range("Tile not found");
	}
}

void Board::setPostion(pair<int, int> position)
{
	this->position = position;
}

pair<int, int> Board::getPosition()
{
	return position;
}

pair<int, int> Board::getSize()
{
	if (board->size())
		return pair<int, int>(board->size(), (*board)[0].size());
	else
		return pair<int, int>(0, 0);
}
