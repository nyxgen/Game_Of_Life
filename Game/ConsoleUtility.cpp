#include "ConsoleUtility.h"

void consoleUtility::gotoxy(int& x, int& y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void consoleUtility::gotoxy(int&& x, int&& y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void consoleUtility::gotoxy(pair<int, int> position)
{
	COORD coord;
	coord.X = position.first;
	coord.Y = position.second;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void consoleUtility::gotoxy(pair<int, int>&& position)
{
	COORD coord;
	coord.X = position.first;
	coord.Y = position.second;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void consoleUtility::showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}