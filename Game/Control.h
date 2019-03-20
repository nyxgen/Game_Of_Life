#pragma once

#include <iostream>
#include <chrono>
#include <curses.h>
#include "Board.h"
#include "ConsoleUtility.h"

namespace control
{
	void setBoard(shared_ptr<Board> board);
	void editBoard(int x, int y);
	char keyboardInput();
	char getLastButtonPressed();
	void moveCursor();
	void setCursorPosition(pair<int, int> position);
	pair<int, int> getCursorPosition();
	bool hasTimeElapsed(long millis);
	bool hasTimeElapsed(chrono::steady_clock::time_point previousTime, long millis);
	chrono::steady_clock::time_point getTime();
	void clockReset();
	pair<int, int> getCursor();
	void copyBoardState(shared_ptr<Board> copyFrom, shared_ptr<Board> copyTo);
}