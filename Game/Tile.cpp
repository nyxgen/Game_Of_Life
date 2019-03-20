#include "Tile.h"


Tile::Tile():alive(false)
{
}


Tile::~Tile()
{
}

bool Tile::isAlive()
{
	return this->alive;
}

void Tile::setAlive()
{
	this->alive = true;
}

void Tile::setDead()
{
	this->alive = false;
}

