#include "./ActionBringToFront.h"

ActionBringToFront::ActionBringToFront(ApplicationManager* pApp, CFigure* sFigure) : Action(pApp) {
	selectedFigure = sFigure;
}

void ActionBringToFront::Execute() {
	
	if (selectedFigure != NULL)
	{
		pManager->BringFigureFront(selectedFigure);
	}
	else
		pManager->GetGUI()-> PrintMessage("Please, select a figure first");
}

void ActionBringToFront::Undo()
{
}

void ActionBringToFront::Redo()
{
}
