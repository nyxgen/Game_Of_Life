#pragma once
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>

#include "Settings.h"
#include "Board.h"

using namespace std;
class FileController
{
public:
	FileController() = delete;
	~FileController() = delete;

	template<class T>
	static void loadFromFile(const T& t, const string& filePath);

	template<class T>
	static void loadStructureFiles(const T& t, const string& directoryPath);
	//static void loadSettings(const string& filePath, const shared_ptr<Settings>& settings);
	//static void loadStructureFiles(const shared_ptr<Settings>& settings);

	//template<class T>
	static void loadStructure(const string& filePath, const shared_ptr<Settings>& settings, const shared_ptr<Board>& board);
	static void saveStructure(const string& filePath, const bool& overwrite, const bool& readyToLoad, const shared_ptr<Settings>& settings, const shared_ptr<Board>& board);
};

template<class T>
inline static void FileController::loadFromFile(const T & t, const string & filePath)
{
	t->loadFromFile(filePath);
}

template<class T>
inline void FileController::loadStructureFiles(const T & t, const string & directoryPath)
{
	t->loadStructureFiles(directoryPath);
}
