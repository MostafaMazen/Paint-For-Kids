#pragma once
#include "Action.h"
#include "../ApplicationManager.h"


class ActionSendToBack :public Action
{
	CFigure* selectedFigure;

public:
	
	ActionSendToBack(ApplicationManager*, CFigure*);


	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};