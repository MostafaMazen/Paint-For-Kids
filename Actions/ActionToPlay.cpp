#include "ActionToPlay.h"

ActionToPlay::ActionToPlay(ApplicationManager* pApp):Action(pApp)
{
}

void ActionToPlay::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	// clear toolbar
	pGUI->ClearDrawingToolBar();
	pGUI->CreatePlayToolBar();
	pGUI->ClearDrawArea();
}
