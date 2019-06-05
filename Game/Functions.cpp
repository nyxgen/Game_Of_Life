
#include "Functions.h"

namespace Functions
{
	vector<pair<void(*)(shared_ptr<Settings>), string>> getFunctions()
	{
		vector<pair<void(*)(shared_ptr<Settings>), string>> functions =
		{
			pair<void(*)(shared_ptr<Settings>), string>(closeWindow, "closeWindow"),
			pair<void(*)(shared_ptr<Settings>), string>(setGameState, "setGameState"),
			pair<void(*)(shared_ptr<Settings>), string>(setResetState, "setResetState"),
			pair<void(*)(shared_ptr<Settings>), string>(setNextState, "setNextState"),
			pair<void(*)(shared_ptr<Settings>), string>(setPrevState, "setPrevState"),
			pair<void(*)(shared_ptr<Settings>), string>(setSetupState, "setSetupState"),
			pair<void(*)(shared_ptr<Settings>), string>(setPauseState, "setPauseState"),
			pair<void(*)(shared_ptr<Settings>), string>(chooseStructureUp, "chooseStructureUp"),
			pair<void(*)(shared_ptr<Settings>), string>(chooseStructureDown, "chooseStructureDown"),
			pair<void(*)(shared_ptr<Settings>), string>(saveBoard, "saveBoard"),
			pair<void(*)(shared_ptr<Settings>), string>(loadBoard, "loadBoard"),
			pair<void(*)(shared_ptr<Settings>), string>(clearBoard, "clearBoard"),
			pair<void(*)(shared_ptr<Settings>), string>(null, "null")
		};
		return functions;
	}

	pointer getFunction(string functionName)
	{
		vector<pair<void(*)(shared_ptr<Settings>), string>> functions = getFunctions();
		for (auto& i : functions)
		{
			if (i.second == functionName)
				return i.first;
		}
		return null;
	}

	void closeWindow(shared_ptr<Settings>settings)
	{
		settings->state("exit");
	}

	void setGameState(shared_ptr<Settings> settings)
	{
		settings->state("game");
	}

	void setResetState(shared_ptr<Settings> settings)
	{
		settings->state("reset");
	}

	void setNextState(shared_ptr<Settings> settings)
	{
		settings->state("next");
	}

	void setPrevState(shared_ptr<Settings> settings)
	{
		settings->state("prev");
	}

	void setSetupState(shared_ptr<Settings> settings)
	{
		settings->state("set");
	}

	void setPauseState(shared_ptr<Settings> settings)
	{
		settings->state("pause");
	}

	void saveBoard(shared_ptr<Settings> settings)
	{
		settings->state("save");
	}

	void loadBoard(shared_ptr<Settings> settings)
	{
		settings->state("load");
	}

	void clearBoard(shared_ptr<Settings> settings)
	{
		settings->state("clear");
	}

	void chooseStructureUp(shared_ptr<Settings> settings)
	{
		settings->chosenFileNumber(settings->chosenFileNumber() + 1);
	}

	void chooseStructureDown(shared_ptr<Settings> settings)
	{
		settings->chosenFileNumber(settings->chosenFileNumber() - 1);
	}

	void null(shared_ptr<Settings> settings) {}

}