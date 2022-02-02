#pragma once
#include "Action.h"
#include "../ApplicationManager.h"


class ActionBringToFront :public Action
{
	CFigure* selectedFigure;

public:

	ActionBringToFront(ApplicationManager*, CFigure*);


	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};