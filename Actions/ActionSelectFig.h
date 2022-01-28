#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include<thread>
#include<future>
#include <string>

class ApplicationFiguresHelperPanelManager;

//Add Square Action class
class ActionSelectFig : public Action
{
	CFigure* figure;
	
public:
	ActionSelectFig(ApplicationManager*, CFigure*);

	

	//Add Square to the ApplicationManager
	virtual void Execute();

};
