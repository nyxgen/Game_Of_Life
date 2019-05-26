#include "Game.h"

namespace game
{
	shared_ptr<Board> gameBoard;
	shared_ptr<Graphics> graphics;
	shared_ptr<Settings> settings;
	shared_ptr<Menu> menu;
}

void game::mainLoop()
{	
	GameStates::init(graphics,gameBoard,settings, menu);
	sf::Clock MainClock;
	int controlTime = 1;
	while (graphics->window()->isOpen())
	{
		sf::Event event;
		while (graphics->window()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				graphics->window()->close();
		}
		sf::Int64 time = MainClock.getElapsedTime().asMicroseconds();
		if (time > controlTime)
		{
			if (settings->state() == "reset")
			{
				GameStates::reset(gameBoard, settings);
				settings->state("pause");
				controlTime = 100000;
			}
			else if (settings->state() == "set")
			{
				GameStates::draw(graphics,gameBoard, settings, menu);
				controlTime = 100000;
			}
			else if (settings->state() == "game")
			{
				GameStates::start(graphics, gameBoard, settings, menu);
				controlTime = 0;
			}
			else if (settings->state() == "next")
			{
				GameStates::next(graphics, gameBoard, settings, menu);
				settings->state("pause");
				controlTime = 100000;
			}
			else if (settings->state() == "pause")
			{
				GameStates::pause(graphics, gameBoard, settings, menu);
				controlTime = 100000;
			}
			else if (settings->state() == "prev")
			{
				GameStates::prev(graphics, gameBoard, settings, menu);
				settings->state("pause");
				controlTime = 100000;
			}
			else if (settings->state() == "save")
			{
				FileController::saveStructure("Structures/Saved", false, true, settings, gameBoard);
				settings->state("pause");
				controlTime = 100000;
			}
			else if (settings->state() == "load")
			{
				gameBoard->clear();
				settings->itterationNumber(0);
				FileController::loadStructure(settings->getFile(), settings, gameBoard);
				settings->state("pause");
				controlTime = 100000;
			}
			else if (settings->state() == "clear")
			{
				gameBoard->clear();
				settings->state("pause");
				controlTime = 100000;
			}
			else
			{
				settings->state("pause");
			}
			MainClock.restart();
		}
		else
		{
			sf::sleep(sf::microseconds(controlTime - time));
		}
		if (settings->itterationNumber() % 50 == 0)
		{
			FileController::saveStructure("Tmp/" + to_string(settings->itterationNumber()), true, false, settings, gameBoard);
		}
	}
}
