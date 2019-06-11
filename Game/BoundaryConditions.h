#pragma once
#include "Board.h"

namespace BoundaryConditions
{
	void initNone(const std::shared_ptr<Board>& board);
	
	void initCylindrical(const std::shared_ptr<Board>& board);

	void initSpherical(const std::shared_ptr<Board>& board);

	void calc(const std::shared_ptr<Board>& board);
};

