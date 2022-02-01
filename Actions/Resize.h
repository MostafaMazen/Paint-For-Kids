#pragma once
#include "Action.h"
#include "../ApplicationManager.h"

class Resize : public Action
{
	CFigure* FigureSelected;
public:
	Resize(ApplicationManager* pAppMgr, CFigure*);

	virtual void Execute();

	virtual void Undo();

	virtual void Redo();
};