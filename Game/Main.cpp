#include "Game.h"
#include <curses.h>

int main()
{
	game::init();
	game::set();
	game::start();


	endwin();
	system("pause");
}