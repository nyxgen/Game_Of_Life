#pragma once

#include <iostream>

using namespace std;

class Tile
{
	bool alive;
public:
	Tile();
	~Tile();
	bool isAlive();
	void setAlive();
	void setDead();

};

