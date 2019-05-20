#include "boundaryCondition.h"

void boundaryCondition::none(const shared_ptr<Board>& board)
{
	sf::Vector2u boardSize = board->size();
	static vector<vector<int>> map;
	map.resize(boardSize.x);
	for (auto& i : map)
	{
		i.clear();
		i.resize(boardSize.y);
	}
	const shared_ptr<vector<pair<int, int>>>& aliveCells = board->aliveCells();

	for (auto& i : (*aliveCells))
	{
		if (i.first - 1 >= 0)
		{
			if (i.second - 1 >= 0)
				++map[i.first - 1][i.second - 1];
			if (i.second + 1 < boardSize.y)
				++map[i.first - 1][i.second + 1];
			++map[i.first - 1][i.second];
		}

		if (i.first + 1 < boardSize.x)
		{
			if (i.second - 1 >= 0)
				++map[i.first + 1][i.second - 1];
			if (i.second + 1 < boardSize.y)
				++map[i.first + 1][i.second + 1];
			++map[i.first + 1][i.second];
		}

		if (i.second - 1 >= 0)
			++map[i.first][i.second - 1];
		if (i.second + 1 < boardSize.y)
			++map[i.first][i.second + 1];
	}

	int k{ 0 };
	int l{ 0 };

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

void boundaryCondition::cylindrical(const shared_ptr<Board>& board)
{
	sf::Vector2u boardSize = board->size();
	static vector<vector<int>> map;
	map.resize(boardSize.x);
	for (auto& i : map)
	{
		i.clear();
		i.resize(boardSize.y);
	}

	const shared_ptr<vector<pair<int, int>>>& aliveCells = board->aliveCells();

	for (auto& i : (*aliveCells))
	{
		if (i.second - 1 >= 0)
		{
			++map[(i.first - 1 + boardSize.x) % boardSize.x][i.second - 1];
			++map[(i.first + boardSize.x) % boardSize.x][i.second - 1];
			++map[(i.first + 1 + boardSize.x) % boardSize.x][i.second - 1];
		}
		if (i.second + 1 < boardSize.y)
		{
			++map[(i.first - 1 + boardSize.x) % boardSize.x][i.second + 1];
			++map[(i.first + boardSize.x) % boardSize.x][i.second + 1];
			++map[(i.first + 1 + boardSize.x) % boardSize.x][i.second + 1];
		}

		++map[(i.first - 1 + boardSize.x) % boardSize.x][i.second];
		++map[(i.first + 1 + boardSize.x) % boardSize.x][i.second];
	}

	int k{ 0 };
	int l{ 0 };

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

void boundaryCondition::spherical(const shared_ptr<Board>& board)
{
	sf::Vector2u boardSize = board->size();
	static vector<vector<int>> map;
	map.resize(boardSize.x);
	for (auto& i : map)
	{
		i.clear();
		i.resize(boardSize.y);
	}

	const shared_ptr<vector<pair<int, int>>>& aliveCells = board->aliveCells();

	for (auto& i : (*aliveCells))
	{
		++map[(i.first - 1 + boardSize.x) % boardSize.x][(i.second - 1 + boardSize.y) % boardSize.y];
		++map[(i.first + boardSize.x) % boardSize.x][(i.second - 1 + boardSize.y) % boardSize.y];
		++map[(i.first + 1 + boardSize.x) % boardSize.x][(i.second - 1 + boardSize.y) % boardSize.y];

		++map[(i.first - 1 + boardSize.x) % boardSize.x][(i.second + 1 + boardSize.y) % boardSize.y];
		++map[(i.first + boardSize.x) % boardSize.x][(i.second + 1 + boardSize.y) % boardSize.y];
		++map[(i.first + 1 + boardSize.x) % boardSize.x][(i.second + 1 + boardSize.y) % boardSize.y];

		++map[(i.first - 1 + boardSize.x) % boardSize.x][i.second];
		++map[(i.first + 1 + boardSize.x) % boardSize.x][i.second];
	}

	int k{ 0 };
	int l{ 0 };
	
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
