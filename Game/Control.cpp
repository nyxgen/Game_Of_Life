#include "Control.h"

namespace control
{
	pair<int, int> cursorPosition = pair<int, int>(0, 0);
	shared_ptr<Board> board;
	auto currentTime = chrono::high_resolution_clock::now();
	auto previousTime = currentTime;
	auto timeElapsed = currentTime - previousTime;
	int lastButtonPressed;
}

void control::setBoard(shared_ptr<Board> board)
{
	control::board = board;
}

void control::editBoard(int x, int y)
{
	if (board.use_count() != 0)
	{

		try
		{
			shared_ptr<Tile> tile = board->getTile(x - board->getPosition().first , y - board->getPosition().second);
			if (tile->isAlive())
			{
				tile->setDead();
			}
			else
			{
				tile->setAlive();
			}
			if (tile->isAlive())
			{

			}
		}
		catch (out_of_range e)	{}
	}
}

char control::keyboardInput()
{
	consoleUtility::gotoxy(0, 0);
	timeout(10);
	consoleUtility::gotoxy(control::cursorPosition);
	lastButtonPressed = getch();
	flushinp();
	return lastButtonPressed;
}

char control::getLastButtonPressed()
{
	return control::lastButtonPressed;
}

void control::moveCursor()
{
	if ((lastButtonPressed == 'a' || lastButtonPressed ==  KEY_LEFT) && control::cursorPosition.first > 0)
	{
		control::cursorPosition.first--;
	}
	else if (lastButtonPressed == 'd' || lastButtonPressed == KEY_RIGHT)
	{
		control::cursorPosition.first++;
	}
	else if ((lastButtonPressed == 'w' || lastButtonPressed == KEY_UP) && control::cursorPosition.second > 0)
	{
		control::cursorPosition.second--;
	}
	else if (lastButtonPressed == 's' || lastButtonPressed == KEY_DOWN)
	{
		control::cursorPosition.second++;
	}
	else if (lastButtonPressed == ' ')
	{
		control::editBoard(control::cursorPosition.first, control::cursorPosition.second);
	}
}

void control::setCursorPosition(pair<int, int> position)
{
	control::cursorPosition = position;
}

pair<int, int> control::getCursorPosition()
{
	return control::cursorPosition;
}

bool control::hasTimeElapsed(long millis)
{
	currentTime = chrono::high_resolution_clock::now();
	timeElapsed = currentTime - previousTime;
	if (chrono::duration_cast<std::chrono::milliseconds>(timeElapsed).count() > millis)
	{
		return true;
	}
	return false;
}

bool control::hasTimeElapsed(chrono::steady_clock::time_point previousTime, long millis)
{
	currentTime = chrono::high_resolution_clock::now();
	timeElapsed = currentTime - previousTime;
	if (chrono::duration_cast<std::chrono::milliseconds>(timeElapsed).count() > millis)
	{
		return true;
	}
	return false;
}

chrono::steady_clock::time_point control::getTime()
{
	return chrono::high_resolution_clock::now();
}

void control::clockReset()
{
	previousTime = chrono::high_resolution_clock::now();
}

pair<int, int> control::getCursor()
{
	return cursorPosition;
}

void control::copyBoardState(shared_ptr<Board> copyFrom, shared_ptr<Board> copyTo)
{
	pair<int, int> copyFromSize = copyFrom->getSize();
	pair<int, int> copyToSize = copyTo->getSize();

	if (copyFromSize.first > copyToSize.first || copyFromSize.second > copyToSize.second)
		return;

	for (int i = 0; i < copyFromSize.first; i++)
	{
		for (int j = 0; j < copyFromSize.second; j++)
		{
			if (copyFrom->getTile(i, j)->isAlive())
				copyTo->getTile(i, j)->setAlive();
			else
				copyTo->getTile(i, j)->setDead();
		}
	}
}
