#pragma once
#include <vector>
#include <iostream>
#include "Settings.h"

using namespace std;

typedef void(*pointer)(shared_ptr<Settings>);

vector<pair<void(*)(shared_ptr<Settings>), string>> getFunctions();

pointer getFunction(string functionName);

void closeWindow(shared_ptr<Settings> settings);

void setGameState(shared_ptr<Settings> settings);

void setResetState(shared_ptr<Settings> settings);

void setNextState(shared_ptr<Settings> settings);

void setPrevState(shared_ptr<Settings> settings);

void setSetupState(shared_ptr<Settings> settings);

void setPauseState(shared_ptr<Settings> settings);

void saveBoard(shared_ptr<Settings> settings);

void loadBoard(shared_ptr<Settings> settings);

void clearBoard(shared_ptr<Settings> settings);

void chooseStructureUp(shared_ptr<Settings> settings);

void chooseStructureDown(shared_ptr<Settings> settings);

void null(shared_ptr<Settings> settings);


