#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\ActionAddEllipse.h"
#include "Actions\ActionSelectFig.h"
#include "Actions\ActionAddHexagon.h"
#include "Actions\Resize.h"
#include <iostream>
#include "MouseState\MouseStatesUtil.h"
#include "DEFS.h"
#include "Actions\ActionSave.h"
#include "Actions/ActionLoad.h"



void ApplicationManager::onEvent(MouseStPoint& data)
{

	ctrlState = data.ctrlKey;   // get ctrl button state

	/* Fixing Screen Error */
	if (data.state == STATE_SIZING || data.state == STATE_PAINTING) {
		std::async(std::launch::async, &ApplicationManager::UpdateInterface,this);
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
			data.delKey = 0;
		}
		cout << "Delete-Key pressed" << endl;
	}

	//cout << "STATE: " <<data.state<< endl;
	//cout << "ActionType: " << ActType << endl;

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
	if (GetSelectedFigure() != -1 && panelListen->stat == PANEL_OPEN) {
		panelListen->appPanelMngr->launchPanal();
	}
	else if (GetSelectedFigure() != -1 && panelListen->stat == PANEL_CLOSE) {
		FigList[GetSelectedFigure()]->SetSelected(false);
		UpdateInterface();
	}
	else if (GetSelectedFigure() != -1 && panelListen->stat == PANAL_SENDING_COLOR) {
		FigList[GetSelectedFigure()]->ChngFillClr(panelListen->selectedObjColor);
		FigList[GetSelectedFigure()]->ChngDrawClr(panelListen->selectedObjColor);
		UpdateInterface();
	}
}

//Constructor
ApplicationManager::ApplicationManager(ThreadNotifier* threadNoti)
{
	this->threadNoti = threadNoti;

	//threadNoti->on("PANEL_START", this);

	cout << "From AppMngr: " << threadNoti << std::endl;
	cout << "From AppMngr ThreadID: " << this_thread::get_id() << std::endl;
	FigCount = x = y = 0;
		
	//Create Input and output
	pGUI = new GUI();

	/* Start Listening on inputs */
	mouseState = pGUI->getMouseState();
	mouseState->on("MOUSE_DOWN", this);
	mouseState->on("MOUSE_MOVE", this);
	mouseState->on("MOUSE_UP", this);
	mouseState->on("DELETE_KEY", this);
	mouseState->on("WIN_SIZING", this);
	mouseState->on("WIN_PAINTING", this);
	this->threadNoti->on("PANEL_START", this);
	this->threadNoti->on("PANEL_CLOSE", this);
	this->threadNoti->on("PANEL_CHANGE_COLOR", this);

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
		UpdateInterface();

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
		case SAVE:
			newAct = new ActionSave(this, FigCount);
			break;

		case LOAD:
			newAct = new ActionLoad(this);
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

void ApplicationManager::DeleteSelectedFigures()
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->IsSelected()) {
			for (int j = i; j < FigCount; j++) {
				FigList[j] = FigList[j + 1];
				if (j + 1 == FigCount) {
					FigList[j] = NULL;
				}
			}
			i--;
			FigCount--;
		}
	}
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
	pGUI->CreateDrawToolBar();
	pGUI->CreateStatusBar();
	if (GetSelectedFigure() != -1) {
		pGUI->PrintMessage(FigList[GetSelectedFigure()]->getFigData());
	}
	pGUI->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
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
