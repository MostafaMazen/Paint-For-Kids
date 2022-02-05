#include "GUI.h"
#include "..\MouseState\MouseStateNotifier.h"
#include <iostream>

//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1300;
	UI.height = 700;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 45;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = NULL;	//Filling color
	UI.MsgColor = BLACK;		//Messages color
	UI.BkGrndColor = color(142,166,225);	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = WHITE;
	UI.PenWidth = 3;	//width of the figures frames

	//Create the output window
	std::map<window*, ApplicationWindowState*> window_mouseState_map;
	window_mouseState_map = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	pWind = window_mouseState_map.begin()->first; // map window state with window reference
	mouseState = window_mouseState_map[pWind]; //access the map fetch the address of window

	mStP.msg = "";


	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
	
}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//


void GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_HXGN: return DRAW_HEX;
			case ITM_RESIZE: return RESIZE;
			case ITM_SEND2BACK: return SEND_BACK;
			case ITM_BRING2FRONT: return BRNG_FRNT;
			case ITM_LOAD:return LOAD;
			case ITM_SAVE:return SAVE;
			case ITM_SWITCH2PLAY:return TO_PLAY_DRAW_TOGGLE;
			case ITM_EXIT: return EXIT;
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_PLAY) {
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_PICK_FIGURETYPE: return GAME_MODE_FIGTYPE;
			case ITM_PICK_FILLCOLOR: return GAME_MODE_FILLCOLOR;
			case ITM_PICK_FILL_TYPE: return GAME_MODE_TYPE_AND_FILL;
			case ITM_SWITCH2DRAW: return TO_PLAY_DRAW_TOGGLE;
			case ITM_EXIT2: return EXIT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}

	/*
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}
	*/
	
}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

std::map<window*, ApplicationWindowState*> GUI::CreateWind(int w, int h, int x, int y) const
{ 
	std::map<window*, ApplicationWindowState*> result;
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	result[pW] = pW->getMouseState();
	return result;
}
ApplicationWindowState* GUI::getMouseState()
{
	//
	return mouseState;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearDrawingToolBar() const
{
	
	std::async(std::launch::async, [this]() {
		pWind->SetPen(WHITE);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
		});
	
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	std::async(std::launch::async, [this]() {
		pWind->SetPen(UI.StatusBarColor, 1);
		pWind->SetBrush(UI.StatusBarColor);
		pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
		});
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	std::async(std::launch::async, [this]() {
		//Clear Status bar by drawing a filled white Square
		pWind->SetPen(UI.StatusBarColor, 1);
		pWind->SetBrush(UI.StatusBarColor);
		pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
		});
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	std::async(std::launch::async, [this]() {
		
		//UI.InterfaceMode = MODE_DRAW; not my job

		pWind->SetPen(WHITE);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

		if (UI.InterfaceMode == MODE_DRAW) {
			string MenuItemImages[DRAW_ITM_COUNT];
			MenuItemImages[ITM_SQUR] = "images\\MenuItems\\square.jpg";
			MenuItemImages[ITM_ELPS] = "images\\MenuItems\\ellipse.jpg";
			MenuItemImages[ITM_HXGN] = "images\\MenuItems\\hexagon.jpg";
			MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\resize.jpg";
			MenuItemImages[ITM_SEND2BACK] = "images\\MenuItems\\s2b.jpg";
			MenuItemImages[ITM_BRING2FRONT] = "images\\MenuItems\\b2f.jpg";
			MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
			MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Menu_Save.jpg";
			MenuItemImages[ITM_SWITCH2PLAY] = "images\\MenuItems\\switch.jpg";
			MenuItemImages[ITM_EXIT] = "images\\MenuItems\\exit.jpg";

			//TODO: Prepare images for each menu item and add it to the list



			//Draw menu item one image at a time
			for (int i = 0; i < DRAW_ITM_COUNT; i++)
				pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);


			//Draw a line under the toolbar
			pWind->SetPen(BLACK, 3);
			pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

		}
		else if (UI.InterfaceMode == MODE_PLAY) {

			pWind->SetPen(WHITE);
			pWind->SetBrush(WHITE);
			pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

			string MenuItemImages[PLAY_ITM_COUNT];
			MenuItemImages[ITM_PICK_FIGURETYPE] = "images\\MenuItems\\shapes.jpg";
			MenuItemImages[ITM_PICK_FILLCOLOR] = "images\\MenuItems\\colors.jpg";
			MenuItemImages[ITM_PICK_FILL_TYPE] = "images\\MenuItems\\shapes&colors.jpg";
			MenuItemImages[ITM_SWITCH2DRAW] = "images\\MenuItems\\switch_off.jpg";
			MenuItemImages[ITM_EXIT2] = "images\\MenuItems\\exit.jpg";
			//TODO: Prepare images for each menu item and add it to the list	


			//Draw menu item one image at a time
			for (int i = 0; i < PLAY_ITM_COUNT; i++)
				pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



			//Draw a line under the toolbar
			pWind->SetPen(BLACK, 3);
			pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

		}

		//You can draw the tool bar icons in any way you want.
		//Below is one possible way

		//First prepare List of images for each menu item
		//To control the order of these images in the menu, 
		//reoder them in UI_Info.h ==> enum DrawMenuItem
		});
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	//DEPRECATED DON'T USE IT PLEAS [JIMMY]
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	std::async(std::launch::async, [this]() {
		pWind->SetPen(UI.BkGrndColor, 1);
		pWind->SetBrush(UI.BkGrndColor);
		pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
		});
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg)	//Prints a message on status bar
{
	std::async(std::launch::async, [this,msg]() {
		mStP.msg = msg;
		mouseState->emit("MSG_CHANGE", mStP);
		ClearStatusBar();	//First clear the status bar

		pWind->SetPen(UI.MsgColor, 50);
		pWind->SetFont(20, BOLD, BY_NAME, "Arial");
		pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
		});
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}


//omar add this function to return crnt background clr to not use ui directly
// to use it in save action
color GUI::getCrntBackgroundColor() const
{
	return UI.BkGrndColor;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width
	
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P1.x +length, P1.y+length, style);
	//pWind->DrawLine(P1.x, P1.y, P1.x + length, P1.y + length, style);

}

//====================================Drawing Elipse====================================//
void GUI::DrawEllipse(Point P1, Point p2, double StartAngle, double EndAngle, GfxInfo EllipseGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = EllipseGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, EllipseGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (EllipseGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(EllipseGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawEllipse(P1.x, P1.y, p2.x, p2.y, style);
	//pWind->DrawArc(P1.x, P1.y, p2.x, p2.y, StartAngle, EndAngle, style);

}

//====================================Drawing Hexagon====================================//

void GUI::DrawHexagon(int* pX, int* pY, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width
	cout << "GUI:: Draw Hexagon" << endl;

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawPolygon(pX, pY, 6, style);
	//	pWind->DrawLine(pX[0], pY[0], pX[1],pY[1], style);

}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

