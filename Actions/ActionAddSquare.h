#pragma once

#include "Action.h"

//Add Square Action class
class ActionAddSquare: public Action
{
private:
	//storing the previous state of the action 
	//CFigure* FigList;
public:
	ActionAddSquare(ApplicationManager *pApp);
	
	//Add Square to the ApplicationManager
	virtual void Execute() ;

	virtual void Undo();

	virtual void Redo();
	
};