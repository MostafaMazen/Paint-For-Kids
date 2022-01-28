#pragma once

#include "ActionSelectFig.h"


ActionSelectFig::ActionSelectFig(ApplicationManager* pApp, CFigure* fig):Action(pApp)
{
	figure = fig;	
	figType = "";
}


void ActionSelectFig::Execute()
{
	CFigure** figList = pManager->getFigList();
	for (int i = pManager->getFigCount()-1; i >= 0; i--) {
		if (figList[i] == figure) {
			if (UI.InterfaceMode == MODE_DRAW) {
				figList[i]->SetSelected(!figList[i]->IsSelected());
				if (figList[i]->IsSelected()) {
					pManager->GetGUI()->PrintMessage(figList[i]->getFigData());
				}
			}
			else {
				/* Check play mode */
				if (pManager->gameMode == -1) {
					MessageBox(pManager->GetGUI()->pWind->getWindow(), "Please select Game mode first", "Alert", MB_OKCANCEL);
				}else if (pManager->gameMode == GAME_MODE_FIGTYPE) {
					if (figType == "") {
						figType = figList[i]->getShapeType();

					}
					pManager->deleteFigure(figList[i]);
				}
				else if(pManager->gameMode == GAME_MODE_FILLCOLOR) {

				}
			}
		}
		else {
			if (pManager->ctrlState == 0) {
				figList[i]->SetSelected(false);
			}
		}
	}
}


