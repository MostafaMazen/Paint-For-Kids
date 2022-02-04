#pragma once

#include "ActionSelectFig.h"
#include "ActionLoadGame.h"


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
					break;
				}
				else {
					manageGame(pManager->gameStates.gameMode, figList[i]);
					break;
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

void ActionSelectFig::Undo()
{
}

void ActionSelectFig::Redo()
{
}


void ActionSelectFig::manageGame(int gameMode, CFigure* figure)
{
	switch(gameMode) {
	case GAME_MODE_FIGTYPE:
		if (pManager->gameStates.figType == "") {
			pManager->gameStates.figType = figure->getShapeType();
			pManager->gameMachineValidCount(GAME_MODE_FIGTYPE);
			MessageBox(pManager->GetGUI()->pWind->getWindow(), "You are playing on FigType mode", "Alert", MB_OKCANCEL);
		}
		else {
			if (figure->getShapeType() == pManager->gameStates.figType) {
				pManager->gameStates.correctAns++;
			}
			else {
				pManager->gameStates.wrongAns++;
			}
			if (pManager->gameStates.correctAns == pManager->gameStates.validShapesCount - 1) {
				/* Display Message */
				std::string message = "Game Finished C: " + to_string(pManager->gameStates.correctAns) + " , R: " + to_string(pManager->gameStates.wrongAns);
				MessageBox(pManager->GetGUI()->pWind->getWindow(), message.c_str(), "Alert", MB_OKCANCEL);
				pManager->GetGUI()->PrintMessage("C: " + to_string(pManager->gameStates.correctAns) + " , R: " + to_string(pManager->gameStates.wrongAns));
				cout << "C: " + to_string(pManager->gameStates.correctAns) + " , R: " + to_string(pManager->gameStates.wrongAns) << endl;
				pManager->resetGame();
				Action* reloadGame = new ActionLoadGame(pManager);
				pManager->ExecuteAction(reloadGame);
			}
		}
		break;
	case GAME_MODE_FILLCOLOR:
		if (pManager->gameStates.figColor == "") {
			pManager->gameStates.figColor = figure->getColor();
			pManager->gameMachineValidCount(GAME_MODE_FILLCOLOR);
			MessageBox(pManager->GetGUI()->pWind->getWindow(), "You are playing on FillColor mode", "Alert", MB_OKCANCEL);
		}
		else {
			if (figure->getColor() == pManager->gameStates.figColor) {
				pManager->gameStates.correctAns++;
			}
			else {
				pManager->gameStates.wrongAns++;
			}
			if (pManager->gameStates.correctAns == pManager->gameStates.validShapesCount - 1) {
				/* Display Message */
				std::string message = "Game Finished C: " + to_string(pManager->gameStates.correctAns) + " , R: " + to_string(pManager->gameStates.wrongAns);
				MessageBox(pManager->GetGUI()->pWind->getWindow(), message.c_str(), "Alert", MB_OKCANCEL);
				pManager->GetGUI()->PrintMessage("C: " + to_string(pManager->gameStates.correctAns) + " , R: " + to_string(pManager->gameStates.wrongAns));
				cout << "C: " + to_string(pManager->gameStates.correctAns) + " , R: " + to_string(pManager->gameStates.wrongAns) << endl;
				pManager->resetGame();
				Action* reloadGame = new ActionLoadGame(pManager);
				pManager->ExecuteAction(reloadGame);
			}
		}
		break;
	case GAME_MODE_TYPE_AND_FILL:
		if (pManager->gameStates.figColor == "" && pManager->gameStates.figType == "") {
			pManager->gameStates.figColor = figure->getColor();
			pManager->gameStates.figType = figure->getShapeType();
			pManager->gameMachineValidCount(GAME_MODE_TYPE_AND_FILL);
			MessageBox(pManager->GetGUI()->pWind->getWindow(), "You are playing on FigType and fillColor mode", "Alert", MB_OKCANCEL);
		}
		else {
			if (figure->getColor() == pManager->gameStates.figColor && figure->getShapeType() == pManager->gameStates.figType) {
				pManager->gameStates.correctAns++;
			}
			else {
				pManager->gameStates.wrongAns++;
			}
			if (pManager->gameStates.correctAns == pManager->gameStates.validShapesCount - 1) {
				/* Display Message */
				std::string message = "Game Finished C: " + to_string(pManager->gameStates.correctAns) + " , R: " + to_string(pManager->gameStates.wrongAns);
				MessageBox(pManager->GetGUI()->pWind->getWindow(), message.c_str(), "Alert", MB_OKCANCEL);
				pManager->GetGUI()->PrintMessage("C: " + to_string(pManager->gameStates.correctAns) + " , R: " + to_string(pManager->gameStates.wrongAns));
				cout << "C: " + to_string(pManager->gameStates.correctAns) + " , R: " + to_string(pManager->gameStates.wrongAns) << endl;
				pManager->resetGame();
				Action* reloadGame = new ActionLoadGame(pManager);
				pManager->ExecuteAction(reloadGame);
			}
		}
		break;
	}

	pManager->deleteFigure(figure);
}
