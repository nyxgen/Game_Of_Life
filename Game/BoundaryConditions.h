#pragma once
#include "Board.h"

namespace BoundaryConditions
{
	void initNone(const shared_ptr<Board>& board);
	
	void initCylindrical(const shared_ptr<Board>& board);

	void initSpherical(const shared_ptr<Board>& board);

	void calc(const shared_ptr<Board>& board);
};

