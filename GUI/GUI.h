#pragma once

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\MouseState\MouseStateNotifier.h"
#include "..\ApllicationManagerState\Header1.h"
#include <map>
#include<future>


//This class is responsible for Grphical User Interface handling
//All user input and program outputs MUST be done through this class
//No other class is allowed to perform direct i/o
class GUI	
{

private:
	ApplicationWindowState* mouseState;

	ApplicationInputStates mStP;
	
public:	
	window* pWind;	//Pointer to the Graphics Window
public:
	GUI();
	~GUI();	
	std::map<window*, ApplicationWindowState*> CreateWind(int, int, int , int) const; //creates the application window

	ApplicationWindowState* getMouseState();
	/////////// Input Functoinality  /////////////////
	void GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	string GetSrting() ;	 //Returns a string entered by the user
	ActionType MapInputToActionType(int& x, int& y) const; //Read the user click and map to an action


	/////////// Output Functoinality  ////////////////
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar

	void ClearDrawingToolBar() const;	//Clears draw toolbar 
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	
	// -- Figures Drawing functions
	void DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a Square
	///TODO: Make similar functions for drawing all other figures.
	void DrawEllipse(Point P1, Point p2, double StartAngle, double EndAngle, GfxInfo EllipseGfxInfo, bool selected) const;//Draw an Ellipse
	void DrawHexagon(int* pX, int* pY, GfxInfo RectGfxInfo, bool selected) const;
	void PrintMessage(string msg);	//Print a message on Status bar

	color getCrntBackgroundColor()const;
	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width


};

