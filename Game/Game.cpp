#include "Game.h"

namespace game
{
	shared_ptr<Board> gameBoard;
	shared_ptr<Graphics> graphics;
	shared_ptr<Settings> settings;
	shared_ptr<Menu> menu;
	sf::Vector2u size;
	sf::Vector2u position;
	sf::Vector2u boardSize;
	string boundaryCondition;
	int itteration;
	int currentFps;
	int targetFps;
}
void game::loadSettings(string filePath)
{
	boost::property_tree::ptree pt;
	try
	{
		boost::property_tree::ini_parser::read_ini(filePath, pt);
	}
	catch (exception e)
	{
		boardSize = sf::Vector2u(10, 10);
		size = sf::Vector2u(10, 10);
		position = sf::Vector2u(10, 10);
		boundaryCondition = "NONE";
	}

	try {
		size = sf::Vector2u(pt.get<int>("Board.SizeX"), pt.get<int>("Board.SizeY"));
	}
	catch (exception e)
	{
		size = sf::Vector2u(10, 10);
	};

	try {
		boardSize = sf::Vector2u(pt.get<int>("Board.BoardSizeX"), pt.get<int>("Board.BoardSizeY"));
	}
	catch (exception e)
	{
		boardSize = sf::Vector2u(400, 400);
	};


	try {
		position = sf::Vector2u(pt.get<int>("Board.PositionX"), pt.get<int>("Board.PositionY"));
	}
	catch (exception e)
	{
		position = sf::Vector2u(10, 10);
	};

	try {
		boundaryCondition = pt.get<string>("Game.BoundaryCondition");
	}
	catch (exception e)
	{
		boundaryCondition = "NONE";
	};
	if (boardSize.x <= 0)
	{
		boardSize.x = 10;
	}
	if (boardSize.y <= 0)
	{
		boardSize.y = 10;
	}

	if (size.x < 2)
		size.x= 2;
	if (size.y < 2)
		size.y = 2;

	if (position.x < 0)
		position.x = 0;
	if (position.y < 0)
		position.y = 0;
}

void game::loadStructureFiles()
{
	for (const auto & entry : boost::filesystem::directory_iterator("Structures"))
	{
		if (entry.path().extension().string() == ".rle")
		{
			settings->addFile("Structures/" + entry.path().filename().string());
		}
	}
}

void game::loadStructure(string filePath)
{
	boost::filesystem::path p{ filePath };
	boost::filesystem::ifstream ifs{ p };
	int x = 0, y = 0;
	int currentPositionX = 0;
	int currentPositionY = 0;
	char data;
	int number = 0;
	
	while (!ifs.eof() && ifs.is_open())
	{
		ifs >> data;
		if (data >= 48 && data <= 57)
		{
			number *= 10;
			number += static_cast<int>(data) - 48;
		}
		else if (data == 'x')
		{
			ifs >> data;
			if (data == '=')
			{
				ifs >> data;
				while (data != ',')
				{
					
					x *= 10;
					x += static_cast<int>(data) - 48;
					ifs >> data;
				}
				if (x > size.x)
					return;
				
			}
			
		}
		else if (data == 'y')
		{
			ifs >> data;
			if (data == '=')
			{
				ifs >> data;
				while (data != ',')
				{

					y *= 10;
					y += static_cast<int>(data) - 48;
					ifs >> data;
				}
				if (y > size.y)
					return;
			}
		}
		else if (data == 'b')
		{
			if (number == 0)
				number = 1;
			for (int i = 0; i < number; i++)
			{
				if (currentPositionX >= x)
				{
					currentPositionX = 0;
					currentPositionY++;
					if (currentPositionY >= y)
						return;
				}
				try {
					gameBoard->alive(currentPositionX, currentPositionY, false);
				}
				catch (exception e) {}
				currentPositionX++;
			}
			number = 0;
			
		}
		else if (data == 'o')
		{
			if (number == 0)
				number = 1;
			for (int i = 0; i < number; i++)
			{
				if (currentPositionX >= x)
				{
					currentPositionX = 0;
					currentPositionY++;
					if (currentPositionY >= y)
						return;
				}
				try {
					gameBoard->alive(currentPositionX, currentPositionY, true);
				}
				catch (exception e)	{}
				currentPositionX++;
				
			}
			number = 0;
		}
		else if (data == '$')
		{
			currentPositionX = 0;
			currentPositionY++;
		}
		else if (data == '!')
		{
		}
	}
	settings->loadedStructure(filePath);
}

void game::saveStructure(string filePath, bool overwrite, bool readyToLoad)
{
	string filePathCopy = filePath;
	int fileNumber = 0;
	if (!overwrite)
	{
		while (boost::filesystem::exists(filePath + ".rle"))
		{
			fileNumber++;
			filePath = filePathCopy + to_string(fileNumber);
		}
	}
	filePath += ".rle";
	boost::filesystem::path p{ filePath };
	boost::filesystem::ofstream ofs{ p };

	sf::Vector2u size = gameBoard->size(); 
	sf::Vector2u currentPosition = sf::Vector2u(0, 0);
	int number = 0;
	ofs << "x = " << size.x << ", y = " << size.y << "," << endl;
	for (int i = 0; i < size.x; i++)
	{
		bool written = false;
		bool lastWrittenAlive = false;
		bool currentAlive = gameBoard->tile(0,i)->alive();
		for (int j = 0; j < size.y; j++)
		{
			if (gameBoard->tile(j, i)->alive() != currentAlive)
			{
				currentAlive = !currentAlive;
				if(number != 1)
					ofs << number;
				if (currentAlive)
				{
					ofs << "b";
					lastWrittenAlive = false;
				}
				else
				{
					ofs << "o";
					lastWrittenAlive = true;
				}
				number = 0;
				written = true;
				
			}
			if (j == size.y - 1)
			{
				if (!written && gameBoard->tile(j, i)->alive())
				{
					if(number != 1)
						ofs << number;
					ofs << "o";
					written = true;
				}
			}
			number++;
		}
		number = 0;
		if ((i != size.x - 1))
		{
			ofs << "$";
		}
	}
	ofs << "!";
	if(readyToLoad)
		settings->addFile(filePath);
}

void game::init()
{
	loadSettings("Config/config.ini");
	size = size;
	gameBoard = make_shared<Board>(size);
	gameBoard->boardSize(boardSize);
	gameBoard->position(position);
	graphics = make_shared<Graphics>();
	graphics->setWindow(make_shared<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Game of life", sf::Style::Fullscreen));
	settings = make_shared<Settings>();
	settings->window(graphics->getWindow());
	loadStructureFiles();
	menu = make_shared<Menu>(settings);
	menu->load("Config/menu.cfg");
	itteration = 0;
	targetFps = 1;
	currentFps = 1;
}

void game::set()
{
	graphics->clear();
	try
	{
		game::changeButtonText(settings->getFile(), "fileBox");
		game::changeButtonText(to_string(currentFps), "fpsBox");
		targetFps = (int)(menu->findButton("fpsSlider")->slider() * 1000);
		if (targetFps <= 0)
			targetFps = 1;
		game::changeButtonText(to_string(targetFps), "fpsSlider");
	}
	catch (exception e) {};
	menu->showMenu();
	menu->checkMenu();
	drawBoard(gameBoard);
	setBoard(gameBoard);
	graphics->display();
}

void game::reset()
{
	gameBoard->clear();
	gameBoard->aliveCells()->clear();
	loadStructure(settings->loadedStructure());
}

void game::start()
{
	static sf::Clock clock;
	graphics->clear();
	try
	{
		game::changeButtonText(to_string(currentFps), "fpsBox");
		targetFps = (int)(menu->findButton("fpsSlider")->slider() * 1000);
		if (targetFps <= 0)
			targetFps = 1;
		game::changeButtonText(to_string(targetFps), "fpsSlider");
	}
	catch (exception e) {};
	menu->showMenu();
	menu->checkMenu();
	drawBoard(gameBoard);
	int time = clock.getElapsedTime().asMicroseconds();
	if (time > 1000000 / targetFps)
	{
		currentFps = 1000000 / time;
		clock.restart();
		nextItteration(gameBoard);
	}
	graphics->display();
}

void game::next()
{
	graphics->clear();
	menu->showMenu();
	menu->checkMenu();
	nextItteration(gameBoard);
	drawBoard(gameBoard);
	graphics->display();
}

void game::prev()
{
	int it = game::itteration - 1;
	if (it < 0)
		return;
	int toLoad = it / 50 * 50;
	gameBoard->aliveCells()->clear();
	game::gameBoard->clear();
	loadStructure("Tmp/" + to_string(toLoad) + ".rle");
	//game::reset();
	game::itteration = toLoad;
	for (int i = 0; i < it-toLoad; i++)
	{
		i = i;
		nextItteration(gameBoard);
	}
	
}

void game::pause()
{
	graphics->clear();
	try
	{
		game::changeButtonText(settings->getFile(), "fileBox");
		game::changeButtonText(to_string(currentFps), "fpsBox");
		targetFps = (int)(menu->findButton("fpsSlider")->slider() * 1000);
		if (targetFps <= 0)
			targetFps = 1;
		game::changeButtonText(to_string(targetFps), "fpsSlider");
	}
	catch (exception e) {};
	menu->showMenu();
	menu->checkMenu();
	drawBoard(gameBoard);
	graphics->display();
}

void game::changeButtonText(string text, string buttonName)
{
	try
	{
		menu->findButton(buttonName)->text(text);
	}
	catch (exception e) {};
}

void game::game()
{	
	game::init();
	sf::Clock MainClock;
	int controlTime = 1;
	while (graphics->getWindow()->isOpen())
	{
		sf::Event event;
		while (graphics->getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				graphics->getWindow()->close();
		}
		int time = MainClock.getElapsedTime().asMicroseconds();
		if (time > controlTime)
		{
			if (settings->state() == "reset")
			{
				game::reset();
				settings->state("pause");
				controlTime = 100000;
			}
			else if (settings->state() == "set")
			{
				game::set();
				controlTime = 100000;
			}
			else if (settings->state() == "game")
			{
				game::start();
				controlTime = 0;
			}
			else if (settings->state() == "next")
			{
				game::next();
				settings->state("pause");
				controlTime = 100000;
			}
			else if (settings->state() == "pause")
			{
				game::pause();
				controlTime = 100000;
			}
			else if (settings->state() == "prev")
			{
				game::prev();
				settings->state("pause");
				controlTime = 100000;
			}
			else if (settings->state() == "save")
			{
				game::saveStructure("Structures/Saved", false, true);
				settings->state("pause");
				controlTime = 100000;
			}
			else if (settings->state() == "load")
			{
				gameBoard->clear();
				game::itteration = 0;
				gameBoard->aliveCells()->clear();
				game::loadStructure(settings->getFile());
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
		if (game::itteration % 50 == 0)
		{
			saveStructure("Tmp/" + to_string(game::itteration), true, false);
		}
	}
}

void game::nextItteration(shared_ptr<Board> board)
{
	if (game::boundaryCondition == "CYLINDRICAL")
		boundaryCondition::cylindrical(board);
	else if (game::boundaryCondition == "SPHERICAL")
		boundaryCondition::spherical(board);
	else
		boundaryCondition::none(board);
	game::itteration++;
}

void game::drawBoard(shared_ptr<Board> board)
{
	static sf::VertexArray va(sf::Quads);
	va.clear();
	if (board->size().x > 0 && board->size().y > 0)
	{
		sf::Vector2u over = sf::Vector2u(15, 15);
		sf::Vector2u size = board->boardSize();
		sf::Vector2u position = board->position();
		sf::RectangleShape rs;
		rs.setSize(sf::Vector2f(size + over + over));
		rs.setPosition(sf::Vector2f(position - over));
		rs.setFillColor(sf::Color(125, 125, 125));
		graphics->getWindow()->draw(rs);

		sf::RectangleShape rs2;
		rs2.setSize(sf::Vector2f(size));
		rs2.setPosition(sf::Vector2f(position));
		rs2.setFillColor(sf::Color::Red);
		graphics->getWindow()->draw(rs2);
	}

	shared_ptr<vector<pair<int, int>>> aliveCells = board->aliveCells();

	for (int i = 0; i < aliveCells->size(); i++)
	{
	vector<sf::Vertex> vertexes = board->tile((*aliveCells)[i].first, (*aliveCells)[i].second)->vertexes();
		for (int k = 0; k < vertexes.size(); k++)
		{
			va.append(vertexes[k]);
		}
	}
	graphics->getWindow()->draw(va);
}

void game::checkBoard(shared_ptr<Board> board)
{
	for (int i = 0; i < board->size().x; i++)
	{
		for (int j = 0; j < board->size().y; j++)
		{
			board->tile(i, j)->targeted();
		}
	}
}

void game::setBoard(shared_ptr<Board> board)
{
	for (int i = 0; i < board->size().x; i++)
	{
		for (int j = 0; j < board->size().y; j++)
		{
			board->tile(i, j)->setState();
		}
	}
}