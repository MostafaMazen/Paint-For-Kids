#include "./ActionSendToBack.h"

ActionSendToBack::ActionSendToBack(ApplicationManager* pApp, CFigure* sFigure) : Action(pApp) {
	selectedFigure = sFigure;
}


void ActionSendToBack::Execute() {
	//calculate the size of the figList 
	
	if (selectedFigure != NULL)
	{
		pManager->SendFigureBack(selectedFigure);
	}
	else
		pManager->GetGUI()-> PrintMessage("Please, select a figure first");
}

void ActionSendToBack::Undo()
{
}

void ActionSendToBack::Redo()
{
}
