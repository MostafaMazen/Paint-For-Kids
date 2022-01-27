#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include<thread>
#include<future>

class ApplicationFiguresHelperPanelManager;

//Add Square Action class
class ActionSelectFig : public Action
{
	ApplicationManager* appMngr;
	CFigure* figure;

	
public:
	ActionSelectFig(ApplicationManager*, CFigure*);

	

	//Add Square to the ApplicationManager
	virtual void Execute();

};
