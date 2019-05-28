#include "GameStates.h"

void GameStates::init(shared_ptr<Graphics>& graphics,shared_ptr<Board>& board, shared_ptr<Settings>& settings, shared_ptr<Menu>& menu, shared_ptr<Control>& control)
{
	graphics = make_shared<Graphics>();
	graphics->window(make_shared<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Game of life", sf::Style::Fullscreen));
	settings = make_shared<Settings>();
	FileController::loadSettings("Config/config.ini", settings);
	board = make_shared<Board>(settings->tilesNumber());
	board->size(settings->size());
	board->position(settings->position());
	settings->window(graphics->window());
	FileController::loadStructureFiles(settings);
	menu = make_shared<Menu>(settings);
	menu->load("Config/menu.cfg");
	settings->itterationNumber(0);
	settings->targetFPS(1);
	settings->currentFPS(1);
	control = make_shared<Control>();

	if (settings->boundaryCondition() == "NONE")
		BoundaryConditions::initNone(board);
	else if (settings->boundaryCondition() == "CYLINDRICAL")
		BoundaryConditions::initCylindrical(board);
	else if (settings->boundaryCondition() == "SPHERICAL")
		BoundaryConditions::initSpherical(board);
}

void GameStates::draw(const shared_ptr<Graphics>& graphics, const shared_ptr<Board>& board, const shared_ptr<Settings>& settings, const shared_ptr<Menu>& menu, const shared_ptr<Control>& control)
{
	graphics->clear();
	settings->targetFPS(static_cast<int>(menu->button("fpsSlider")->slider() * 1000));
	if (settings->targetFPS() <= 0)
		settings->targetFPS(1);
	try
	{
		menu->button("fileBox")->text(settings->getFile());
		menu->button("fpsBox")->text(to_string(settings->currentFPS()));
		menu->button("fpsSlider")->text(to_string(settings->targetFPS()));
	}
	catch (exception e) {};
	control->checkMouseActions(menu);
	control->checkMouseActions(board);
	graphics->draw(menu);
	graphics->draw(board);
	graphics->display();
}

void GameStates::reset(const shared_ptr<Board>& board, const shared_ptr<Settings>& settings)
{
	board->clear();
	FileController::loadStructure(settings->loadedStructure(), settings, board);
}

void GameStates::next(const shared_ptr<Graphics>& graphics, const shared_ptr<Board>& board, const shared_ptr<Settings>& settings, const shared_ptr<Menu>& menu, const shared_ptr<Control>& control)
{
	graphics->clear();
	control->checkMouseActions(menu);
	GameStates::nextItteration(board, settings);
	graphics->draw(menu);
	graphics->draw(board);
	graphics->display();
}

void GameStates::nextItteration(const shared_ptr<Board>& board, const shared_ptr<Settings>& settings)
{
	BoundaryConditions::calc(board);
	settings->itterationNumber(settings->itterationNumber() + 1);
}

void GameStates::pause(const shared_ptr<Graphics>& graphics, const shared_ptr<Board>& board, const shared_ptr<Settings>& settings, const shared_ptr<Menu>& menu, const shared_ptr<Control>& control)
{
	graphics->clear();
	try
	{
		settings->targetFPS(static_cast<int>(menu->button("fpsSlider")->slider() * 1000));
		if (settings->targetFPS() <= 0)
			settings->targetFPS(1);
		menu->button("fileBox")->text(settings->getFile());
		menu->button("fpsBox")->text(to_string(settings->currentFPS()));
		menu->button("fpsSlider")->text(to_string(settings->targetFPS()));
	}
	catch (exception e) {};
	control->checkMouseActions(menu);
	graphics->draw(menu);
	graphics->draw(board);
	graphics->display();
}

void GameStates::prev(const shared_ptr<Graphics>& graphics, const shared_ptr<Board>& board, const shared_ptr<Settings>& settings, const shared_ptr<Menu>& menu)
{
	int it = settings->itterationNumber() - 1;
	if (it < 0)
		return;
	int toLoad = it / 50 * 50;
	board->clear();
	FileController::loadStructure("Tmp/" + to_string(toLoad) + ".rle", settings, board);
	settings->itterationNumber(toLoad);
	for (int i = 0; i < it - toLoad; i++)
	{
		i = i;
		GameStates::nextItteration(board, settings);
	}

}

void GameStates::start(const shared_ptr<Graphics>& graphics, const shared_ptr<Board>& board, const shared_ptr<Settings>& settings, const shared_ptr<Menu>& menu, const shared_ptr<Control>& control)
{
	static sf::Clock clock;
	graphics->clear();
	try
	{
		settings->targetFPS(static_cast<int>(menu->button("fpsSlider")->slider() * 1000));
		if (settings->targetFPS() <= 0)
			settings->targetFPS(1);
		menu->button("fileBox")->text(settings->getFile());
		menu->button("fpsBox")->text(to_string(settings->currentFPS()));
		menu->button("fpsSlider")->text(to_string(settings->targetFPS()));
		
	}
	catch (exception e) {};
	control->checkMouseActions(menu);
	graphics->draw(menu);
	graphics->draw(board);
	sf::Int64 time = clock.getElapsedTime().asMicroseconds();
	if (time > 1000000 / settings->targetFPS())
	{
		settings->currentFPS(1000000 / static_cast<int>(time));
		clock.restart();
		GameStates::nextItteration(board, settings);
	}
	graphics->display();
}