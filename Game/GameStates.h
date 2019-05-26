#pragma once
#include "Board.h"
#include "Graphics.h"
#include "Settings.h"
#include "Menu.h"
#include "FileController.h"
#include "BoundaryConditions.h"

class GameStates
{
public:
	GameStates() = delete;
	~GameStates() = delete;
	static void init(shared_ptr<Graphics>& graphics, shared_ptr<Board>& board, shared_ptr<Settings>& settings, shared_ptr<Menu>& menu);
	static void draw(const shared_ptr<Graphics>& graphics, const shared_ptr<Board>& board, const shared_ptr<Settings>& settings, const shared_ptr<Menu>& menu);
	static void reset(const shared_ptr<Board>& board, const shared_ptr<Settings>& settings);
	static void next(const shared_ptr<Graphics>& graphics, const shared_ptr<Board>& board, const shared_ptr<Settings>& settings, const shared_ptr<Menu>& menu);
	static void nextItteration(const shared_ptr<Board>& board, const shared_ptr<Settings>& settings);
	static void pause(const shared_ptr<Graphics>& graphics, const shared_ptr<Board>& board, const shared_ptr<Settings>& settings, const shared_ptr<Menu>& menu);
	static void prev(const shared_ptr<Graphics>& graphics, const shared_ptr<Board>& board, const shared_ptr<Settings>& settings, const shared_ptr<Menu>& menu);
	static void start(const shared_ptr<Graphics>& graphics, const shared_ptr<Board>& board, const shared_ptr<Settings>& settings, const shared_ptr<Menu>& menu);
};

