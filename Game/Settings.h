#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
class Settings
{
	shared_ptr<sf::RenderWindow> _window;
	string _state;
	string _loadedStructure;
	vector<string> _fileList;
	int _chosenFileNumber;
public:
	Settings();
	~Settings();

	void window(const shared_ptr<sf::RenderWindow>& window);
	const shared_ptr<sf::RenderWindow>& window();

	void state(const string& state);
	const string& state();

	const vector<string>& fileList();
	void addFile(const string& path);

	const int& chosenFileNumber();
	void chosenFileNumber(const int& chosen);
	const string& getFile();

	void loadedStructure(const string& path);
	const string& loadedStructure();
};

