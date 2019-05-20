#include "Settings.h"

Settings::Settings()
{
	_state = "set";
	_chosenFileNumber = 0;
}

Settings::~Settings()
{
}

void Settings::window(const shared_ptr<sf::RenderWindow>& window)
{
	_window = window;
}

const shared_ptr<sf::RenderWindow>& Settings::window()
{
	return _window;
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
