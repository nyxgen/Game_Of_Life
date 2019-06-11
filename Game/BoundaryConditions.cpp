#include "BoundaryConditions.h"

using namespace std;
using numberU = sf::Vector2u;

void BoundaryConditions::initNone(const shared_ptr<Board>& board)
{
	numberU tilesNumber = board->tilesCount();
	unsigned int k{ 0 };
	unsigned int l{ 0 };
	for (auto& i : (*board->tiles()))
	{
		for (auto&j : i)
		{
			j->clearNeighbours();
			if (k >= 1)
			{
				if (l >= 1)
					j->addNeighbour((*board)(k - 1, l - 1));
				if (l + 1 < tilesNumber.y)
					j->addNeighbour((*board)(k - 1, l + 1));
				j->addNeighbour((*board)(k - 1, l));
			}

			if (k + 1 < tilesNumber.x)
			{
				if (l >= 1)
					j->addNeighbour((*board)(k + 1, l - 1));
				if (l + 1 < tilesNumber.y)
					j->addNeighbour((*board)(k + 1, l + 1));
				j->addNeighbour((*board)(k + 1, l));
			}

			if (l >= 1)
				j->addNeighbour((*board)(k, l - 1));
			if (l + 1 < tilesNumber.y)
				j->addNeighbour((*board)(k, l + 1));
			++l;
		}
		++k;
		l = 0;
	}
}

void BoundaryConditions::initCylindrical(const shared_ptr<Board>& board)
{
	numberU tilesNumber = board->tilesCount();
	unsigned int k{ 0 };
	unsigned int l{ 0 };
	for (auto& i : (*board->tiles()))
	{
		for (auto&j : i)
		{
			j->clearNeighbours();
			if (l >= 1)
			{
				j->addNeighbour((*board)((k - 1 + tilesNumber.x) % tilesNumber.x, l - 1));
				j->addNeighbour((*board)((k + tilesNumber.x) % tilesNumber.x, l - 1));
				j->addNeighbour((*board)((k + 1 + tilesNumber.x) % tilesNumber.x, l - 1));
			}
			if (l + 1 < tilesNumber.y)
			{
				j->addNeighbour((*board)((k - 1 + tilesNumber.x) % tilesNumber.x, l + 1));
				j->addNeighbour((*board)((k + tilesNumber.x) % tilesNumber.x, l + 1));
				j->addNeighbour((*board)((k + 1 + tilesNumber.x) % tilesNumber.x, l + 1));
			}

			j->addNeighbour((*board)((k - 1 + tilesNumber.x) % tilesNumber.x, l));
			j->addNeighbour((*board)((k + 1 + tilesNumber.x) % tilesNumber.x, l));
			++l;
		}
		++k;
		l = 0;
	}
}


void BoundaryConditions::initSpherical(const shared_ptr<Board>& board)
{
	numberU tilesNumber = board->tilesCount();
	unsigned int k{ 0 };
	unsigned int l{ 0 };

	for (auto& i : (*board->tiles()))
	{
		for (auto&j : i)
		{
			j->clearNeighbours();
			j->addNeighbour((*board)((k - 1 + tilesNumber.x) % tilesNumber.x, (l - 1 + tilesNumber.y) % tilesNumber.y));
			j->addNeighbour((*board)((k + tilesNumber.x) % tilesNumber.x,(l - 1 + tilesNumber.y) % tilesNumber.y));
			j->addNeighbour((*board)((k + 1 + tilesNumber.x) % tilesNumber.x,(l - 1 + tilesNumber.y) % tilesNumber.y));

			j->addNeighbour((*board)((k - 1 + tilesNumber.x) % tilesNumber.x,(l + 1 + tilesNumber.y) % tilesNumber.y));
			j->addNeighbour((*board)((k + tilesNumber.x) % tilesNumber.x,(l + 1 + tilesNumber.y) % tilesNumber.y));
			j->addNeighbour((*board)((k + 1 + tilesNumber.x) % tilesNumber.x, (l + 1 + tilesNumber.y) % tilesNumber.y));

			j->addNeighbour((*board)((k - 1 + tilesNumber.x) % tilesNumber.x, l));
			j->addNeighbour((*board)((k+ 1 + tilesNumber.x) % tilesNumber.x, l));
			++l;
		}
		++k;
		l = 0;
	}
}

void BoundaryConditions::calc(const shared_ptr<Board>& board)
{
	numberU tilesNumber = board->tilesCount();
	static vector<vector<int>> map;
	map.resize(tilesNumber.x);
	for (auto& i : map)
	{
		i.clear();
		i.resize(tilesNumber.y);
	}

	unsigned int k{ 0 };
	unsigned int l{ 0 };

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
			if (j == 3 || (j == 2 && (*board)(k, l)->alive()))
			{
				board->alive(k, l, true);
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
