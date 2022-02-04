#include "ActionToPlayToDrawToggle.h"
#include "ActionLoadGame.h"
ActionToPlayDrawToggle::ActionToPlayDrawToggle(ApplicationManager* pApp):Action(pApp)
{
	appMngr = pApp;
}

void ActionToPlayDrawToggle::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	//make this button toggling
	//THIS SUPPOSE TO WORK ONLY AS TOGGLING
	pGUI->ClearDrawingToolBar(); //updare interface his job is to clean the screen according to the the mode we are in 		
	if (UI.InterfaceMode == MODE_DRAW) {
		UI.InterfaceMode = MODE_PLAY;
		Action* act = new ActionLoadGame(appMngr);
		appMngr->ExecuteAction(act);
		std::async(std::launch::async, [this, &pGUI]() {
			pGUI->CreateDrawToolBar();
			});
	}
	else {
		UI.InterfaceMode = MODE_DRAW;
		//appmng delete all the figs from the list 
		appMngr->resetGame();
		appMngr->RemoveAllFigs();
		std::async(std::launch::async, [this, &pGUI]() {
			pGUI->CreateDrawToolBar();
			});
	}
}

void ActionToPlayDrawToggle::Undo()
{
}

void ActionToPlayDrawToggle::Redo()
{
}
