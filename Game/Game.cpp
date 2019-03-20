#include "Game.h"

#define BACKGROUND 1
#define ALIVE 2
#define DEAD 3
#define CURSOR_ALIVE 4
#define CURSOR_DEAD 5

namespace game
{
	shared_ptr<Board> setupBoard;
	shared_ptr<WINDOW> setupBoardWindow;

	shared_ptr<Board> gameBoard;
	shared_ptr<WINDOW> gameBoardWindow;

	pair<int, int> size;
	pair<int, int> position;
	string boundaryCondition;
}
void game::loadSettings(string path)
{
	boost::property_tree::ptree pt;
	try
	{
		boost::property_tree::ini_parser::read_ini(path, pt);
	}
	catch (exception e)
	{
		size = pair<int, int>(10, 10);
		position = pair<int, int>(10, 10);
		boundaryCondition = "NONE";
	}

	try {
		size = pair<int, int>(pt.get<int>("Board.SizeX"), pt.get<int>("Board.SizeY"));
	}
	catch (exception e)
	{
		size = pair<int, int>(10, 10);
	};

	try {
		position = pair<int, int>(pt.get<int>("Board.PositionX"), pt.get<int>("Board.PositionY"));
	}
	catch (exception e)
	{
		position = pair<int, int>(10, 10);
	};

	try {
		boundaryCondition = pt.get<string>("Game.BoundaryCondition");
	}
	catch (exception e)
	{
		boundaryCondition = "NONE";
	};

	if (size.first < 2)
		size.first = 2;
	if (size.second < 2)
		size.second = 2;

	if (position.first < 0)
		position.first = 0;
	if (position.second < 0)
		position.second = 0;

}

void game::init()
{
	initscr();
	start_color();
	loadSettings("config.ini");
	setupBoard = make_shared<Board>(Board(size.first, size.second));
	gameBoard = make_shared<Board>(Board(size.first, size.second));
	setupBoardWindow = make_shared<WINDOW>(*newwin(size.second+2, size.first+2, position.second, position.first));
	gameBoardWindow = make_shared<WINDOW>(*newwin(size.second+2, size.first+2, position.second, position.first*2+5));

	setupBoard->setPostion(pair<int, int>(position.first+1, position.second+1));
	gameBoard->setPostion(pair<int, int>(position.first*2+6, position.second+1));
	control::setCursorPosition(setupBoard->getPosition());

	start_color();
	init_pair(1, COLOR_BLUE, COLOR_CYAN);
	init_pair(2, COLOR_BLUE, COLOR_GREEN);
	init_pair(3, COLOR_BLUE, COLOR_RED);
	init_pair(4, COLOR_YELLOW, COLOR_GREEN);
	init_pair(5, COLOR_YELLOW, COLOR_RED);

	consoleUtility::showConsoleCursor(false);
	control::setBoard(setupBoard);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	refresh();
	wbkgd(setupBoardWindow.get(), COLOR_PAIR(BACKGROUND));
	box(setupBoardWindow.get(), 0, 0);
	wrefresh(setupBoardWindow.get());
	wbkgd(gameBoardWindow.get(), COLOR_PAIR(BACKGROUND));
	box(gameBoardWindow.get(), 0, 0);
	wrefresh(gameBoardWindow.get());

	control::clockReset();
}
void game::set()
{
	while ((control::getLastButtonPressed() != 'p') && (control::getLastButtonPressed() != 10))
	{
		if (control::hasTimeElapsed(150))
		{
			control::clockReset();
			control::keyboardInput();
			displayBoard(setupBoard, setupBoardWindow);
			displayCursor(setupBoardWindow);
		}
	}
	control::copyBoardState(setupBoard, gameBoard);
}

void game::start()
{
	while ((control::getLastButtonPressed()!= 'e') && (control::getLastButtonPressed() != 27))
	{
		if (control::hasTimeElapsed(500))
		{
			control::keyboardInput();
			control::clockReset();
			displayBoard(setupBoard, setupBoardWindow);
			displayBoard(gameBoard, gameBoardWindow);
			game::nextItteration();
		}
	}
}

void game::nextItteration()
{
	if (game::boundaryCondition == "CYLINDRICAL")
		boundaryCondition::cylindrical(gameBoard);
	else if (game::boundaryCondition == "SPHERICAL")
		boundaryCondition::spherical(gameBoard);
	else
		boundaryCondition::none(gameBoard);
}

void game::displayBoard(shared_ptr<Board> board, shared_ptr<WINDOW> window)
{
	refresh();
	for (int i = 0; i < board->getSize().first; i++)
	{
		for (int j = 0; j < board->getSize().second; j++)
		{
			if (board->getTile(i, j)->isAlive())
			{
				attron(COLOR_PAIR(ALIVE));
				mvaddch(board->getPosition().second + j, board->getPosition().first + i, ' ');
				attroff(COLOR_PAIR(ALIVE));
			}
			else
			{
				attron(COLOR_PAIR(DEAD));
				mvaddch(board->getPosition().second + j, board->getPosition().first + i, ' ');
				attroff(COLOR_PAIR(DEAD));
			}
		}
	}
}

void game::displayCursor(shared_ptr<WINDOW> window)
{
	control::moveCursor();
	if (control::getCursorPosition().first < (window->_begx + window->_curx + 1))
		control::setCursorPosition(pair<int, int>(window->_begx + window->_curx + 1, control::getCursorPosition().second));
	if (control::getCursorPosition().first > (window->_begx + window->_maxx - 2))
		control::setCursorPosition(pair<int, int>(window->_begx + window->_maxx - 2, control::getCursorPosition().second));
	if (control::getCursorPosition().second < (window->_begy + window->_cury + 1))
		control::setCursorPosition(pair<int, int>(control::getCursorPosition().first, window->_begy + window->_cury + 1));
	if (control::getCursorPosition().second > (window->_begy + window->_maxy - 2))
		control::setCursorPosition(pair<int, int>(control::getCursorPosition().first, window->_begy + window->_maxy - 2));

	static bool blink = true;
	if (blink)
	{
		attron(COLOR_PAIR(CURSOR_ALIVE));
		mvaddch(control::getCursorPosition().second, control::getCursorPosition().first, ' ');
		blink = false;
		attroff(COLOR_PAIR(3));
	}
	{
		try {
			if (setupBoard->getTile(control::getCursorPosition().first - setupBoard->getPosition().first, control::getCursorPosition().second - setupBoard->getPosition().second)->isAlive())
			{
				attron(COLOR_PAIR(CURSOR_ALIVE));
				mvaddch(control::getCursorPosition().second, control::getCursorPosition().first, '*');
				attroff(COLOR_PAIR(CURSOR_ALIVE));
			}
			else
			{
				attron(COLOR_PAIR(CURSOR_DEAD));
				mvaddch(control::getCursorPosition().second, control::getCursorPosition().first, '*');
				attroff(COLOR_PAIR(CURSOR_DEAD));
			}
		}
		catch (exception e)
		{
			attron(COLOR_PAIR(CURSOR_ALIVE));
			mvaddch(control::getCursorPosition().second, control::getCursorPosition().first, ' ');
			blink = false;
			attroff(COLOR_PAIR(CURSOR_ALIVE));
		}
		blink = true;
	}
}

