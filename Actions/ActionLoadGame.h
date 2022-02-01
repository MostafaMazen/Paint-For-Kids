#pragma once

#include "Action.h"
#include<string>

class ActionLoadGame :public Action
{
private:
	string GameFileName;
public:
	ActionLoadGame(ApplicationManager* pApp);
	virtual void Execute();

	virtual void Undo();

	virtual void Redo();
};