#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

#include "Graphics.h"
#include "Board.h"
#include "BoundaryConditions.h"
#include "Menu.h"
#include "Settings.h"
#include "FileController.h"
#include "GameStates.h"

namespace game
{
	void mainLoop();
}