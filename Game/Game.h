#pragma once
#include "Graphics.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

#include "Board.h"
#include "boundaryCondition.h"
#include "Control.h"
#include "Menu.h"
#include "Settings.h"



namespace game
{
	void loadSettings(string filePath);
	void loadStructureFiles();
	void loadStructure(string filePath);
	void saveStructure(string filePath, bool overwrite, bool readyToLoad);
	void changeButtonText(string text, string buttonName);
	void init();
	void set();
	void start();
	void next();
	void prev();
	void game();
	void reset();
	void pause();
	void nextItteration(shared_ptr<Board> board);
	void drawBoard(shared_ptr<Board> board);
	void checkBoard(shared_ptr<Board> board);
	void setBoard(shared_ptr<Board> board);
}