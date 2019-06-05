#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include "Settings.h"


Settings::Settings()
{
}

Settings::~Settings()
{
}

void Settings::loadFromFile(const string & filePath)
{
	boost::property_tree::ptree pt;
	try
	{
		boost::property_tree::ini_parser::read_ini(filePath, pt);
	}
	catch (exception e)
	{
		_tilesNumber = sf::Vector2u(10, 10);
		_size = sf::Vector2u(10, 10);
		_position = sf::Vector2u(10, 10);
		_boundaryCondition = "NONE";
	}

	try {
		_tilesNumber = sf::Vector2u(pt.get<int>("Board.TilesInRow"), pt.get<int>("Board.TilesInColumn"));
	}
	catch (exception e)
	{
		_tilesNumber = sf::Vector2u(10, 10);
	};

	try {
		_size = sf::Vector2u(pt.get<int>("Board.HorizontalBoardSize"), pt.get<int>("Board.VerticalBoardSize"));
	}
	catch (exception e)
	{
		_size = sf::Vector2u(400, 400);
	};


	try {
		_position = sf::Vector2u(pt.get<int>("Board.HorizontalBoardPosition"), pt.get<int>("Board.HorizontalBoardPosition"));
	}
	catch (exception e)
	{
		_position = sf::Vector2u(10, 10);
	};

	try {
		_boundaryCondition = pt.get<string>("Game.BoundaryCondition");
	}
	catch (exception e)
	{
		_boundaryCondition = "NONE";
	};
	if (_tilesNumber.x <= 0)
	{
		_tilesNumber = sf::Vector2u(10, _tilesNumber.y);
	}
	if (_tilesNumber.y <= 0)
	{
		_tilesNumber = sf::Vector2u(_tilesNumber.x, 10);
	}

	if (_size.x < 2)
		_size = sf::Vector2u(10, _size.y);
	if (_size.y < 2)
		_size = sf::Vector2u(_size.x, 10);

	if (_position.x < 0)
		_position = sf::Vector2u(0, _position.y);
	if (_position.y < 0)
		_position = sf::Vector2u(_position.x, 10);
}

void Settings::loadStructureFiles(const string & directoryPath)
{
	for (const auto & entry : boost::filesystem::directory_iterator(directoryPath))
	{
		if (entry.path().extension().string() == ".rle")
		{
			_fileList.push_back(directoryPath + "/" + entry.path().filename().string());
		}
	}
}

void Settings::state(const string& state)
{
	_state = state;
}

const string& Settings::state()
{
	return _state;
}

const vector<string>& Settings::fileList()
{
	return _fileList;
}

void Settings::addFile(const string& path)
{
	_fileList.push_back(path);
}

const int& Settings::chosenFileNumber()
{
	return _chosenFileNumber;
}

void Settings::chosenFileNumber(const int& chosen)
{
	if (chosen >= static_cast<int>(_fileList.size()))
		_chosenFileNumber = 0;
	else if (chosen < 0)
		_chosenFileNumber = static_cast<int>(_fileList.size()) - 1;
	else
		_chosenFileNumber = chosen;
}

const string& Settings::getFile()
{
	if (static_cast<int>(_fileList.size()) == 0)
		return "Null";
	return _fileList[_chosenFileNumber];
}

void Settings::loadedStructure(const string& path)
{
	_loadedStructure = path;
}

const string& Settings::loadedStructure()
{
	return _loadedStructure;
}

void Settings::size(const sf::Vector2u & size)
{
	_size = size;
}

const sf::Vector2u & Settings::size()
{
	return _size;
}

void Settings::tilesNumber(const sf::Vector2u & tilesNumber)
{
	_tilesNumber = tilesNumber;
}

const sf::Vector2u & Settings::tilesNumber()
{
	return _tilesNumber;
}

void Settings::position(const sf::Vector2u & position)
{
	_position = position;
}

const sf::Vector2u & Settings::position()
{
	return _position;
}

void Settings::boundaryCondition(const string & bc)
{
	_boundaryCondition = bc;
}

const string & Settings::boundaryCondition()
{
	return _boundaryCondition;
}

void Settings::itterationNumber(const int & itterationNumber)
{
	_itterationNumber = itterationNumber;
}

const int & Settings::itterationNumber()
{
	return _itterationNumber;
}

void Settings::currentFPS(const int & currentFPS)
{
	_currentFps = currentFPS;
}

const int& Settings::currentFPS()
{
	return _currentFps;
}

void Settings::targetFPS(const int & targetFPS)
{
	_targetFps = targetFPS;
}

const int& Settings::targetFPS()
{
	return _targetFps;
}