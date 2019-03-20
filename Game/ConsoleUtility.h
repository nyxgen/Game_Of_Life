#pragma once
#include <iostream>
#include <windows.h> 

using namespace std;

namespace consoleUtility
{
	void gotoxy(int& x, int& y);
	void gotoxy(int&& x, int&& y);
	void gotoxy(pair<int, int> position);
	void gotoxy(pair<int, int>&& position);
	void showConsoleCursor(bool showFlag);
}
