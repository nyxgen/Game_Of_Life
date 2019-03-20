#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <curses.h>
#include "Board.h"
#include "ConsoleUtility.h"
#include "boundaryCondition.h"
#include "Control.h"


namespace game
{
	void loadSettings(string path);
	void init();
	void set();
	void start();
	void nextItteration();
	void displayBoard(shared_ptr<Board> board, shared_ptr<WINDOW> window);
	void displayCursor(shared_ptr<WINDOW> window);
}