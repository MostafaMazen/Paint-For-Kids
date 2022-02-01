#pragma once

#include "..\DefS.h"

class ApplicationManager; //forward class declaration


//Base class for all possible actions
class Action
{
protected:
	ApplicationManager *pManager;	//Actions needs AppMngr to do their job

	//recording the prev state of the application 
	CFigure* FigListOldState[200]; //this pointer will point to the current state of the shapes  
	CFigure* FigListlatestState[200]; //thsi pointer will point to the latest state has applied from the action

public:

	Action(ApplicationManager *pApp) { pManager = pApp; }	//constructor

	//Execute action (code depends on action type)
	virtual void Execute() =0;

	//To undo this action (code depends on action type)
	//undo should call the old state of the application
	//we will scan the history of the action has applied on the application 
	//then we will pop the last action and save it then redo will push it again 
	virtual void Undo()=0;

	//To redo this action (code depends on action type)
	//redo will check the state of the application and will reset it again 
	virtual void Redo()=0;

};
