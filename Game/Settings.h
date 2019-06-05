#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
class Settings
{
	string _state{ "set" };
	string _loadedStructure;
	vector<string> _fileList;
	int _chosenFileNumber{ 0 };
	sf::Vector2u _size;
	sf::Vector2u _position;
	sf::Vector2u _tilesNumber;
	string _boundaryCondition;
	int _itterationNumber;
	int _currentFps;
	int _targetFps;
public:
	Settings();
	~Settings();

	void loadFromFile(const string& filePath);
	void loadStructureFiles(const string& directoryPath);
	void state(const string& state);
	const string& state();

	const vector<string>& fileList();
	void addFile(const string& path);

	const int& chosenFileNumber();
	void chosenFileNumber(const int& chosen);
	const string& getFile();

	void loadedStructure(const string& path);
	const string& loadedStructure();

	void size(const sf::Vector2u& size);
	const sf::Vector2u& size();

	void tilesNumber(const sf::Vector2u& tilesNumber);
	const sf::Vector2u& tilesNumber();

	void position(const sf::Vector2u& position);
	const sf::Vector2u& position();

	void boundaryCondition(const string& bc);
	const string& boundaryCondition();
	
	void itterationNumber(const int& itterationNumber);
	const int& itterationNumber();

	void currentFPS(const int& currentFPS);
	const int& currentFPS();

	void targetFPS(const int& targetFPS);
	const int& targetFPS();
};


