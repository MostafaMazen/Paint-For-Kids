#pragma once
#include"Action.h"
#include <string>

class ActionSave :public Action {
private:
	int figCount;
	string myFileName;


public:
	ActionSave(ApplicationManager* pApp, int FigCount);
	virtual void Execute();

	virtual void Undo();

	virtual void Redo();

};