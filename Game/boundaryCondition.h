#pragma once
#include "Board.h"

namespace boundaryCondition
{
	void none(const shared_ptr<Board>& board);
	
	void cylindrical(const shared_ptr<Board>& board);

	void spherical(const shared_ptr<Board>& board);
};

