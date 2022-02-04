#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\ActionAddEllipse.h"
#include "Actions\ActionSelectFig.h"
#include "Actions\ActionAddHexagon.h"
#include "Actions\ActionToPlayToDrawToggle.h"
#include "Actions\Resize.h"
#include "Actions/ActionSendToBack.h"
#include "Actions/ActionBringToFront.h"
#include <iostream>
#include "MouseState\MouseStatesUtil.h"
#include "DEFS.h"
#include "Actions\ActionSave.h"
#include "Actions/ActionLoad.h"



void ApplicationManager::onEvent(ApplicationInputStates& data)
{
	ctrlState = data.ctrlKey;   // get ctrl button state
	f1State = data.f1Key;   // get f1 button state

	/* Fixing Screen Error */
	if (data.state == STATE_SIZING || data.state == STATE_PAINTING) {

		std::async(std::launch::async, &ApplicationManager::UpdateInterface,this);
		std::async(std::launch::async, &GUI::CreateStatusBar, pGUI);
		std::async(std::launch::async, [this]() {
			pGUI->CreateDrawToolBar();
			});
	}

	// case delete button is pressed
	if (data.delKey == 1) {
		// check if there is any selected figure
		int index = GetSelectedFigure();
		if (index != -1) {
			DeleteSelectedFigures();
			pGUI->PrintMessage("The Selected Figures have been Deleted!");
			pGUI->ClearDrawArea();
			UpdateInterface();
		}
		data.delKey = 0;
		cout << "Delete-Key pressed" << endl;
	}

	/* Moving the selected figure */
	if (GetSelectedFigure() != -1 && data.mouseDown == true) {
		if (FigList[GetSelectedFigure()]->hasPoint(data.x, data.y)) {
			cout << "MOUSE DOWN: " << data.mouseDown << endl;
			FigList[GetSelectedFigure()]->setCenterPoint(data.x, data.y);
			cout << "dataX: " << data.x << "   y: " << data.y << endl;
			std::async(std::launch::async, &ApplicationManager::UpdateInterface, this);
		}
	}
}

void ApplicationManager::onMessageRecieved(PanelListener* panelListen)
{
	if ((GetSelectedFigure() != -1 || f1State ==1) && panelListen->stat == PANEL_OPEN) {
		if (UI.InterfaceMode == MODE_DRAW) {
			panelListen->appPanelMngr->launchPanal();
		}
	}
	else if (GetSelectedFigure() != -1 && panelListen->stat == PANEL_CLOSE) {
		FigList[GetSelectedFigure()]->SetSelected(false);
		UpdateInterface();
	}
	else if (panelListen->stat == PANAL_SENDING_COLOR) {
		
		switch (panelListen->target) {
		case BACKGROUND:
			UI.BkGrndColor = panelListen->selectedObjColor;
			pGUI->PrintMessage("Background color set to : " + panelListen->selectedObjColor.toHexa());
			break;
		case DRAWING:
			UI.DrawColor = panelListen->selectedObjColor;
			pGUI->PrintMessage("Drawing color set to : " + panelListen->selectedObjColor.toHexa());
			break;
		case FILLING:
			UI.FillColor = panelListen->selectedObjColor;
			pGUI->PrintMessage("Filing color set to : " + panelListen->selectedObjColor.toHexa());
			break;
		case FIGURE:
			if (GetSelectedFigure() != -1) {
				FigList[GetSelectedFigure()]->ChngFillClr(panelListen->selectedObjColor);
				FigList[GetSelectedFigure()]->ChngDrawClr(panelListen->selectedObjColor);
			}
			break;
		}

		std::async(std::launch::async, &ApplicationManager::UpdateInterface, this);
	}
}

//Constructor
ApplicationManager::ApplicationManager(ThreadNotifier* threadNoti)
{
	this->threadNoti = threadNoti;

	resetGame();

	cout << "From AppMngr: " << threadNoti << std::endl;
	cout << "From AppMngr ThreadID: " << this_thread::get_id() << std::endl;
	FigCount = x = y = 0;
		
	//Create Input and output
	pGUI = new GUI();

	/* Start Listening on inputs */
	appWindowState = pGUI->getMouseState();
	appWindowState->on("MOUSE_DOWN", this);
	appWindowState->on("MOUSE_MOVE", this);
	appWindowState->on("MOUSE_UP", this);
	appWindowState->on("DELETE_KEY", this);
	appWindowState->on("CTRL_KEY", this);
	appWindowState->on("F1_KEY", this);
	appWindowState->on("WIN_SIZING", this);
	appWindowState->on("WIN_PAINTING", this);
	//mouseState->on("MSG_CHANGE", this);

	this->threadNoti->on("PANEL_START", this);
	this->threadNoti->on("PANEL_CLOSE", this);
	this->threadNoti->on("PANEL_CHANGE_COLOR", this);

	//initializing intial appMode state 
	UI.InterfaceMode = MODE_DRAW; // INTIAL STATE


	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}
void ApplicationManager::Run()
{
	do
	{
		//1- Read user action
		ActType = pGUI->MapInputToActionType(x, y);

		/* Check if user want to select a figure */
		if (ActType == DRAWING_AREA) {
			pGUI->PrintMessage("");
			if (GetFigure(x, y) != NULL) {	//check if any figure has been clicked
				ActType = SELECT_FIG;		//change actType
			}
			else {
				UnSelectAllFigs();
			}
		}

		//2- Create the corresponding Action
		Action* pAct = CreateAction(ActType);

		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		std::async(std::launch::async, &ApplicationManager::UpdateInterface, this);

	}while(ActType != EXIT);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType& ActType) 
{
	Action* newAct = NULL;
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;

		case DRAW_ELPS:
			newAct = new ActionAddEllipse(this);
			break;

		case DRAW_HEX:
			newAct = new ActionAddHexagon(this);
			break;

		case SELECT_FIG:
			newAct = new ActionSelectFig(this, GetFigure(x, y));
			break;

		case RESIZE:
			if (GetSelectedFigure() != -1) {
				newAct = new Resize(this, FigList[GetSelectedFigure()]);
			}
			else {
				pGUI->PrintMessage("Please select a figure first to resize it!");
			}
			break;
		case SEND_BACK:
			if (GetSelectedFigure() != -1) {
				newAct = new ActionSendToBack(this, FigList[GetSelectedFigure()]);
			}
			break;
		case BRNG_FRNT:
			if (GetSelectedFigure() != -1) {
				newAct = new ActionBringToFront(this, FigList[GetSelectedFigure()]);
			}
			break;
		case SAVE:
			newAct = new ActionSave(this, FigCount);
			break;

		case LOAD:
			newAct = new ActionLoad(this);
			break;

		case TO_PLAY_DRAW_TOGGLE:
			newAct = new ActionToPlayDrawToggle(this);
			break;
		case GAME_MODE_FIGTYPE:
			/* Add action for this mode */
			if (!gameStates.isPlaying) {
				std::cout << "GAME_MODE_FIG_TYPE_SELECTED" << std::endl;
				gameStates.gameMode = GAME_MODE_FIGTYPE;
				gameStates.isPlaying = true;
			}
			else {
				MessageBox(pGUI->pWind->getWindow(), "Please complete the game first to change the mode.", "Alert", MB_OKCANCEL);
			}
			break;
		case GAME_MODE_FILLCOLOR:
			/* Add action for this mode */
			if (!gameStates.isPlaying) {
				std::cout << "GAME_MODE_FILL_COLOR_SELECTED" << std::endl;
				gameStates.gameMode = GAME_MODE_FILLCOLOR;
				gameStates.isPlaying = true;
			}
			else {
				MessageBox(pGUI->pWind->getWindow(), "Please complete the game first to change the mode.", "Alert", MB_OKCANCEL);
			}
			break;
		case GAME_MODE_TYPE_AND_FILL:
			/* Add action for this mode */
			if (!gameStates.isPlaying) {
				std::cout << "GAME_MODE_FILL_TYPE_SELECTED" << std::endl;
				gameStates.gameMode = GAME_MODE_TYPE_AND_FILL;
				gameStates.isPlaying = true;
			}
			else {
				MessageBox(pGUI->pWind->getWindow(), "Please complete the game first to change the mode.", "Alert", MB_OKCANCEL);
			}
			break;
		case EXIT:
			if (MessageBox(pGUI->pWind->getWindow(), "Are you sure?", "Close", MB_OKCANCEL) == IDOK)
			{
				pl.threadClose = true;
				this->threadNoti->emit("THREAD_CLOSE", &pl);
				this->threadNoti->emit("PANEL_FORCE_CLOSE", &pl);
				DestroyWindow(pGUI->pWind->getWindow());
			}
			else {
				ActType = DRAWING_AREA;
			} 
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;
	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}

//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

int ApplicationManager::getFigCount()
{
	return FigCount;
}

void ApplicationManager::gameMachineValidCount(int PLAY_MODE)
{
	switch (PLAY_MODE)
	{
	case GAME_MODE_FIGTYPE:
		for (int i = 0; i < FigCount; i++) {
			if (FigList[i]->getShapeType() == gameStates.figType) {
				gameStates.validShapesCount++;
			}
			else {
				gameStates.inValidShapesCount++;
			}
		}
		break;
	case GAME_MODE_FILLCOLOR:
		//TODO error prone area
		for (int i = 0; i < FigCount; i++) {
			if (FigList[i]->getColor() == gameStates.figColor) {
				gameStates.validShapesCount++;
			}
			else {
				gameStates.inValidShapesCount++;
			}
		}
		break;
	case GAME_MODE_TYPE_AND_FILL:
		//TODO error prone area
		for (int i = 0; i < FigCount; i++) {
			if (FigList[i]->getColor() == gameStates.figColor && FigList[i]->getShapeType() == gameStates.figType) {
				gameStates.validShapesCount++;
			}
			else {
				gameStates.inValidShapesCount++;
			}
		}
		break;
	default:
		std::cout << "unknown Error happen ! <<<< "<<std::endl;
		break;
	}
}

CFigure** ApplicationManager::getFigList()
{
	return FigList;
}

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}

void ApplicationManager::deleteFigure(CFigure* pFig)
{

	std::async(std::launch::async, [this , pFig]() {
		int index = 0;
		for (int i = 0; i < FigCount; i++) {
			if (FigList[i] == pFig) {
				delete pFig;
				index = i;
				break;
			}
		}

		for (int i = index; i < FigCount; i++) {
			FigList[i] = FigList[i + 1];
			if (i + 1 == FigCount) {
				FigList[i] = NULL;
				FigCount--;
			}
		}
		});
}

void ApplicationManager::DeleteSelectedFigures()
{
	
	std::async(std::launch::async, [this]() {
		for (int i = 0; i < FigCount; i++) {
			if (FigList[i]->IsSelected()) {
				delete FigList[i];
				for (int j = i; j < FigCount; j++) {
					FigList[j] = FigList[j + 1];
					if (j + 1 == FigCount) {
						FigList[j] = NULL;
						//ERROR PRONE EREA
					}
				}
				i--;
				FigCount--;
			}
		}
		});
}

//sendBack & bringToFront
void ApplicationManager::SendFigureBack(CFigure* selectedFigure)
{
	
	//check for any shape selected 
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->IsSelected()) {
			CFigure* temp = selectedFigure;
			int swappingIndex = 0;
			for (int i = 0; i < FigCount; i++)
				if (selectedFigure == FigList[i])
				{
					swappingIndex = i;
					break;
				}

			for (int i = swappingIndex; i > 0; i--)
				FigList[i] = FigList[i - 1];
			FigList[0] = temp;
		}
		
	}
	return;
	
	
}

void ApplicationManager::BringFigureFront(CFigure* selectedFigure)
{
	//check if any shape selected on the board 
	//check for any shape selected 
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->IsSelected()) {
			CFigure* temp = selectedFigure;
			int swappingIndex = 0;
			for (int i = 0; i < FigCount; i++)
				if (selectedFigure == FigList[i])
					swappingIndex = i;

			for (int i = swappingIndex; i < FigCount - 1; i++)
				FigList[i] = FigList[i + 1];
			FigList[FigCount - 1] = temp;
		}
		
	}
	return;
	
}

CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL

	/* select first on top */
	for (int i = FigCount - 1; i >= 0; i--) {
		if (FigList[i]->hasPoint(x, y)) {
			return FigList[i];
		}
	}
	return NULL;
}
int ApplicationManager::GetSelectedFigure() const
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->IsSelected()) {
			return i;
		}
	}
	return -1;
}
void ApplicationManager::UnSelectAllFigs() const
{
	for (int i = 0; i < FigCount; i++) {
		FigList[i]->SetSelected(false);
	}
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{		
	std::async(std::launch::async, [this]() {
		std::cout << UI.InterfaceMode << std::endl;
		//if (UI.InterfaceMode == MODE_PLAY) {
		//	pGUI->ClearDrawingToolBar(); //updare interface his job is to clean the screen according to the the mode we are in 		
		//	std::async(std::launch::async, [this]() {
		//		pGUI->CreateDrawToolBar();
		//		});
		//}

		//std::this_thread::sleep_for(60ms);
		if (GetSelectedFigure() != -1) {
			pGUI->PrintMessage(FigList[GetSelectedFigure()]->getFigData());
		}
		pGUI->ClearDrawArea();
		for (int i = 0; i < FigCount; i++)
			FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
		});

}

void ApplicationManager::resetGame()
{
	gameStates.gameMode = -1;
	gameStates.validShapesCount = 0;
	gameStates.inValidShapesCount = 0;
	gameStates.figType = "";
	gameStates.correctAns = 0;
	gameStates.wrongAns = 0;
	gameStates.figColor = "";
	gameStates.isPlaying = false;
}

////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}

static std::mutex s_mutex;
//add and load functionality //////////////////////////////////////////////////////////
std::string ApplicationManager::saveFile(HWND hwnd) {

	const std::string title = "Select a File";
	std::string filename(MAX_PATH, '\0');

	OPENFILENAMEA ofn = { };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files\0 *.TXT";
	ofn.lpstrFile = &filename[0];  // use the std::wstring buffer directly
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = title.c_str();
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
	
	ofn.nFilterIndex = 1;
	GetSaveFileNameA(&ofn);
	std::string result;	
	result = ofn.lpstrFile;
	return result;
}

std::string ApplicationManager::openFile(HWND hwnd)
{

	const std::string title = "Select a File";
	std::string filename(MAX_PATH, '\0');

	OPENFILENAMEA ofn = { };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files\0 *.TXT";
	ofn.lpstrFile = &filename[0];  // use the std::wstring buffer directly
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = title.c_str();
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
	ofn.nFilterIndex = 1;
	GetOpenFileName(&ofn);
	std::string result;
	result = ofn.lpstrFile;
	return result;
}

void ApplicationManager::SaveFigs(ofstream& file) {
	for (int i = 0; i < FigCount; i++)
		FigList[i]->Save(file);
}

void ApplicationManager::RemoveAllFigs()  //for each figure FigList, make it points to NULL 
{
	for (int i = 0; i < FigCount; ++i)
		FigList[i] = NULL;
	FigCount = 0;
}

//add and load functionality //////////////////////////////////////////////////////////
