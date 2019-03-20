#pragma once
#include "Board.h"

namespace boundaryCondition
{
	void none(shared_ptr<Board> board);
	void cylindrical(shared_ptr<Board> board);
	void spherical(shared_ptr<Board> board);
};

