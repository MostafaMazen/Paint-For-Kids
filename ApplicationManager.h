#pragma once

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "MouseState\MouseStateNotifier.h"
#include "MouseState\MouseStateEventHandler.h"
#include "ApllicationManagerState\Header1.h"
#include "ApplicationFiguresHelperPanel/ApplicationFiguresHelperPanel.h"
#include "ApplicationServices\ThreadNotifier.h"
#include<future>
#include<thread>

class Action;	//Forward Declaration


//void myThread(ApplicationManagerState* appMngState);
//
//std::future<void> startThread(ApplicationManagerState* appMngState);

//Main class that manages everything in the application.
class ApplicationManager: public MouseEventHandler, public ThreadEventsHandler
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	PanelListener pl;
	bool flag;
	//bool targetObjSelected;
	ActionType ActType;
	int FigCount, x, y;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	MouseStateNotifier* mouseState;
	ApplicationManagerState* appManagerState;
	//Pointers to Input and Output classes
	GUI* pGUI;
	bool isPlaying; // isPlaying , all game mode icons no more listen 
	
public:

	int gameMode; // start playing the game 

	//for (MULTI SELECT)
	int ctrlState;      // ctrl button state used in select action

	//saving and loading functionality /////////////////////////////////////////
	std::string openFile(HWND hwnd);

	std::string saveFile(HWND hwnd);

	void SaveFigs(ofstream& Out);

	void RemoveAllFigs(); //used to remove exists figs to load new ones

	//saving and loading functionality /////////////////////////////////////////

	//ApplicationFiguresHelperPanelManager* panelManeger;
	ThreadNotifier* threadNoti;

	virtual void onEvent(MouseStPoint &data);
	virtual void onMessageRecieved(PanelListener* panelListen);
	ApplicationManager(ThreadNotifier* threadNoti);
	~ApplicationManager();
	void resetPlayingFlag();
	void Run();		//to run the application

	// -- Action-Related Functions
	Action* CreateAction(ActionType&);
	void ExecuteAction(Action*&) ; //Execute an action
	
	// -- Figures Management Functions
	int getFigCount();				// get current figures count
	CFigure** getFigList();			// get all figures
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	void deleteFigure(CFigure* pFig);	// delete specific figure
	void DeleteSelectedFigures(); // Delets all selected figures
	CFigure* GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	int GetSelectedFigure() const; //Search for a figure given a point inside the figure
	void UnSelectAllFigs() const; // make all figures un selected

	// -- Interface Management Functions	
	GUI *GetGUI() const; //Return pointer to the interface
	void UpdateInterface() const;	//Redraws all the drawing window	

};