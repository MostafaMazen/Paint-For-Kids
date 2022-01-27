#pragma once

#include "ActionSelectFig.h"


ActionSelectFig::ActionSelectFig(ApplicationManager* pApp, CFigure* fig):Action(pApp)
{
	appMngr = pApp;
	figure = fig;
	
}


void ActionSelectFig::Execute()
{
	CFigure** figList = appMngr->getFigList();
	for (int i = appMngr->getFigCount()-1; i >= 0; i--) {
		if (figList[i] == figure) {
			figList[i]->SetSelected(!figList[i]->IsSelected());
			if (figList[i]->IsSelected()) {
				appMngr->GetGUI()->PrintMessage(figList[i]->getFigData());
			}
		}
		else {
			if (appMngr->ctrlState == 0) {
				figList[i]->SetSelected(false);
			}
		}
	}
}
