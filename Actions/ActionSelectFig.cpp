#pragma once

#include "ActionSelectFig.h"


ActionSelectFig::ActionSelectFig(ApplicationManager* pApp, CFigure* fig):Action(pApp)
{
	figure = fig;
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
				if (pManager->gameStates.gameMode == -1) {
					MessageBox(pManager->GetGUI()->pWind->getWindow(), "Please select Game mode first", "Alert", MB_OKCANCEL);
				}else if (pManager->gameStates.gameMode == GAME_MODE_FIGTYPE) {
					if (pManager->gameStates.figType == "") {
						pManager->gameStates.figType = figList[i]->getShapeType();
						pManager->gameMachineValidCount(pManager->gameStates.figType);
					}
					else {
						if (figList[i]->getShapeType() == pManager->gameStates.figType) {
							pManager->gameStates.correctAns++;
						}
						else {
							pManager->gameStates.wrongAns++;
						}
						if (pManager->gameStates.correctAns == pManager->gameStates.validShapesCount - 1) {
							/* Dsplay Message */
							std::string message = "Game Finished C: " + to_string(pManager->gameStates.correctAns) + " , R: " + to_string(pManager->gameStates.wrongAns);
							MessageBox(pManager->GetGUI()->pWind->getWindow(), message.c_str(), "Alert", MB_OKCANCEL);
							pManager->GetGUI()->PrintMessage("C: " + to_string(pManager->gameStates.correctAns) + " , R: " + to_string(pManager->gameStates.wrongAns));
							cout << "C: " + to_string(pManager->gameStates.correctAns) + " , R: " + to_string(pManager->gameStates.wrongAns)<<endl;
						}
					}
					pManager->deleteFigure(figList[i]);
				}
				else if(pManager->gameStates.gameMode == GAME_MODE_FILLCOLOR) {

				}

				break;
			}
		}
		else {
			if (pManager->ctrlState == 0) {
				figList[i]->SetSelected(false);
			}
		}
	}
}


