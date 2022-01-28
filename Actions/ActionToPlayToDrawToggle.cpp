#include "ActionToPlayToDrawToggle.h"

ActionToPlayDrawToggle::ActionToPlayDrawToggle(ApplicationManager* pApp):Action(pApp)
{
}

void ActionToPlayDrawToggle::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	//make this button toggling 
	//THIS SUPPOSE TO WORK ONLY AS TOGGLING 
	if (UI.InterfaceMode == MODE_DRAW) {
		UI.InterfaceMode = MODE_PLAY;		
	}
	else {
		UI.InterfaceMode = MODE_DRAW;
	}	
	//pGUI->ClearDrawArea();
}
