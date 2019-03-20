#include "boundaryCondition.h"

void boundaryCondition::none(shared_ptr<Board> board)
{
	pair<int, int> boardSize = board->getSize();
	vector<vector<int>> map(boardSize.first);
	for (int i = 0; i < boardSize.first; i++)
	{
		map[i] = vector<int>(boardSize.second);
	}

	for (int i = 0; i < boardSize.first; i++)
	{
		for (int j = 0; j < boardSize.second; j++)
		{
			if (board->getTile(i, j)->isAlive())
			{
				if (i - 1 >= 0)
				{
					if (j - 1 >= 0)
						map[i - 1][j - 1]++;
					if (j + 1 < boardSize.second)
						map[i - 1][j + 1]++;
					map[i - 1][j]++;
				}

				if (i + 1 < boardSize.first)
				{
					if (j - 1 >= 0)
						map[i + 1][j - 1]++;
					if (j + 1 < boardSize.second)
						map[i + 1][j + 1]++;
					map[i + 1][j]++;
				}

				if (j - 1 >= 0)
					map[i][j - 1]++;
				if (j + 1 < boardSize.second)
					map[i][j + 1]++;
			}
		}
	}
	for (int i = 0; i < boardSize.first; i++)
	{
		for (int j = 0; j < boardSize.second; j++)
		{
			if (map[i][j] == 3)
			{
				board->getTile(i, j)->setAlive();
			}
			else if (board->getTile(i, j)->isAlive() && map[i][j] == 2)
			{
				board->getTile(i, j)->setAlive();
			}
			else
			{
				board->getTile(i, j)->setDead();
			}
		}
	}
}

void boundaryCondition::cylindrical(shared_ptr<Board> board)
{
	pair<int, int> boardSize = board->getSize();
	vector<vector<int>> map(boardSize.first);
	for (int i = 0; i < boardSize.first; i++)
	{
		map[i] = vector<int>(boardSize.second);
	}

	for (int i = 0; i < boardSize.first; i++)
	{
		for (int j = 0; j < boardSize.second; j++)
		{
			if (board->getTile(i, j)->isAlive())
			{
				if (j - 1 >= 0)
				{
					map[(i - 1 + boardSize.first) % boardSize.first][j - 1]++;
					map[(i + boardSize.first) % boardSize.first][j - 1]++;
					map[(i + 1 + boardSize.first) % boardSize.first][j - 1]++;
				}
				if (j + 1 < boardSize.second)
				{
					map[(i - 1 + boardSize.first) % boardSize.first][j + 1]++;
					map[(i + boardSize.first) % boardSize.first][j + 1]++;
					map[(i + 1 + boardSize.first) % boardSize.first][j + 1]++;
				}

				map[(i - 1 + boardSize.first) % boardSize.first][j]++;
				map[(i + 1 + boardSize.first) % boardSize.first][j]++;
			}
		}
	}
	for (int i = 0; i < boardSize.first; i++)
	{
		for (int j = 0; j < boardSize.second; j++)
		{
			if (map[i][j] == 3)
			{
				board->getTile(i, j)->setAlive();
			}
			else if (board->getTile(i, j)->isAlive() && map[i][j] == 2)
			{
				board->getTile(i, j)->setAlive();
			}
			else
			{
				board->getTile(i, j)->setDead();
			}
		}
	}
}

void boundaryCondition::spherical(shared_ptr<Board> board)
{
	pair<int, int> boardSize = board->getSize();
	vector<vector<int>> map(boardSize.first);
	for (int i = 0; i < boardSize.first; i++)
	{
		map[i] = vector<int>(boardSize.second);
	}

	for (int i = 0; i < boardSize.first; i++)
	{
		for (int j = 0; j < boardSize.second; j++)
		{
			if (board->getTile(i, j)->isAlive())
			{
				map[(i - 1 + boardSize.first) % boardSize.first][(j - 1 + boardSize.second) % boardSize.second]++;
				map[(i + boardSize.first) % boardSize.first][(j - 1 + boardSize.second) % boardSize.second]++;
				map[(i + 1 + boardSize.first) % boardSize.first][(j - 1 + boardSize.second) % boardSize.second]++;

				map[(i - 1 + boardSize.first) % boardSize.first][(j + 1 + boardSize.second) % boardSize.second]++;
				map[(i + boardSize.first) % boardSize.first][(j + 1 + boardSize.second) % boardSize.second]++;
				map[(i + 1 + boardSize.first) % boardSize.first][(j + 1 + boardSize.second) % boardSize.second]++;

				map[(i - 1 + boardSize.first) % boardSize.first][j]++;
				map[(i + 1 + boardSize.first) % boardSize.first][j]++;
			}
		}
	}
	for (int i = 0; i < boardSize.first; i++)
	{
		for (int j = 0; j < boardSize.second; j++)
		{
			if (map[i][j] == 3)
			{
				board->getTile(i, j)->setAlive();
			}
			else if (board->getTile(i, j)->isAlive() && map[i][j] == 2)
			{
				board->getTile(i, j)->setAlive();
			}
			else
			{
				board->getTile(i, j)->setDead();
			}
		}
	}
}
