#pragma once

#include "Action.h"

//Add Square Action class
class ActionAddSquare: public Action
{
public:
	ActionAddSquare(ApplicationManager *pApp);
	
	//Add Square to the ApplicationManager
	virtual void Execute() ;
	
};