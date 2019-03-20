#pragma once

#include <vector>
#include "Tile.h"
#include "ConsoleUtility.h"

using namespace std;
using namespace consoleUtility;

class Board
{
	shared_ptr<vector<vector<shared_ptr<Tile>>>> board = make_shared<vector<vector<shared_ptr<Tile>>>>();
	pair<int, int> position;
public:
	Board() = delete;
	Board(int& sizeX, int& sizeY);
	Board(int&& sizeX, int&& sizeY);
	~Board();
	shared_ptr<Tile> getTile(int positionX, int positionY);
	void setPostion(pair<int, int> position);
	pair<int, int> getPosition();
	pair<int, int> getSize();

};

