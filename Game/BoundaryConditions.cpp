#include "BoundaryConditions.h"

void BoundaryConditions::initNone(const shared_ptr<Board>& board)
{
	sf::Vector2u boardSize = board->tilesCount();
	int k{ 0 };
	int l{ 0 };
	for (auto& i : (*board->tiles()))
	{
		for (auto&j : i)
		{
			j->clearNeighbours();
			if (k - 1 >= 0)
			{
				if (l - 1 >= 0)
					j->addNeighbour(board->tile(k - 1, l - 1));
				if (l + 1 < boardSize.y)
					j->addNeighbour(board->tile(k - 1, l + 1));
				j->addNeighbour(board->tile(k - 1, l));
			}

			if (k + 1 < boardSize.x)
			{
				if (l - 1 >= 0)
					j->addNeighbour(board->tile(k + 1, l - 1));
				if (l + 1 < boardSize.y)
					j->addNeighbour(board->tile(k + 1, l + 1));
				j->addNeighbour(board->tile(k + 1, l));
			}

			if (l - 1 >= 0)
				j->addNeighbour(board->tile(k, l - 1));
			if (l + 1 < boardSize.y)
				j->addNeighbour(board->tile(k, l + 1));
			++l;
		}
		++k;
		l = 0;
	}
}

void BoundaryConditions::initCylindrical(const shared_ptr<Board>& board)
{
	sf::Vector2u boardSize = board->tilesCount();
	int k{ 0 };
	int l{ 0 };
	for (auto& i : (*board->tiles()))
	{
		for (auto&j : i)
		{
			j->clearNeighbours();
			if (l - 1 >= 0)
			{
				j->addNeighbour(board->tile((k - 1 + boardSize.x) % boardSize.x, l - 1));
				j->addNeighbour(board->tile((k + boardSize.x) % boardSize.x, l - 1));
				j->addNeighbour(board->tile((k + 1 + boardSize.x) % boardSize.x, l - 1));
			}
			if (l + 1 < boardSize.y)
			{
				j->addNeighbour(board->tile((k - 1 + boardSize.x) % boardSize.x, l + 1));
				j->addNeighbour(board->tile((k + boardSize.x) % boardSize.x, l + 1));
				j->addNeighbour(board->tile((k + 1 + boardSize.x) % boardSize.x, l + 1));
			}

			j->addNeighbour(board->tile((k - 1 + boardSize.x) % boardSize.x, l));
			j->addNeighbour(board->tile((k + 1 + boardSize.x) % boardSize.x, l));
			++l;
		}
		++k;
		l = 0;
	}
}


void BoundaryConditions::initSpherical(const shared_ptr<Board>& board)
{
	sf::Vector2u boardSize = board->tilesCount();
	int k{ 0 };
	int l{ 0 };

	for (auto& i : (*board->tiles()))
	{
		for (auto&j : i)
		{
			j->clearNeighbours();
			j->addNeighbour(board->tile((k - 1 + boardSize.x) % boardSize.x, (l - 1 + boardSize.y) % boardSize.y));
			j->addNeighbour(board->tile((k + boardSize.x) % boardSize.x,(l - 1 + boardSize.y) % boardSize.y));
			j->addNeighbour(board->tile((k + 1 + boardSize.x) % boardSize.x,(l - 1 + boardSize.y) % boardSize.y));

			j->addNeighbour(board->tile((k - 1 + boardSize.x) % boardSize.x,(l + 1 + boardSize.y) % boardSize.y));
			j->addNeighbour(board->tile((k + boardSize.x) % boardSize.x,(l + 1 + boardSize.y) % boardSize.y));
			j->addNeighbour(board->tile((k + 1 + boardSize.x) % boardSize.x, (l + 1 + boardSize.y) % boardSize.y));

			j->addNeighbour(board->tile((k - 1 + boardSize.x) % boardSize.x, l));
			j->addNeighbour(board->tile((k+ 1 + boardSize.x) % boardSize.x, l));
			++l;
		}
		++k;
		l = 0;
	}
}

void BoundaryConditions::calc(const shared_ptr<Board>& board)
{
	sf::Vector2u boardSize = board->tilesCount();
	static vector<vector<int>> map;
	map.resize(boardSize.x);
	for (auto& i : map)
	{
		i.clear();
		i.resize(boardSize.y);
	}

	int k{ 0 };
	int l{ 0 };

	for (auto& i : (*board->tiles()))
	{
		for (auto& j : i)
		{
			if (j->alive())
			{
				for (auto& m : j->neighbours())
				{
					++map[m->coords().x][m->coords().y];
				}
			}
			++l;
		}
		++k;
		l = 0;
	}

	k = 0;
	l = 0;

	for (auto& i : map)
	{
		for (auto& j : i)
		{
			if (j == 3)
			{
				board->alive(k, l, true);
			}
			else if (board->tile(k, l)->alive() && j == 2)
			{
				//board->alive(k, l, true);
			}
			else
			{
				board->alive(k, l, false);
			}
			++l;
		}
		++k;
		l = 0;
	}
}
