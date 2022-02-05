#pragma once

#include "..\defs.h"
#include "..\GUI\GUI.h"
#include "..\MouseState\MouseStateEventHandler.h"

//Base class for all figures
class CFigure
{
protected:
	Point center;
	static int sharedID;		//Each figure has an ID
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	
	/// Add more parameters if needed.

public:
	int factorPosition = 2;
	CFigure(GfxInfo FigureGfxInfo);
	CFigure();
	void SetSelected(bool );	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	virtual void setPoint(int x, int y) = 0;
	virtual void setCenterPoint(int x, int y) = 0;
	virtual void setSize(float factor) = 0;
	virtual Point getPoint() = 0;
	virtual void DrawMe(GUI*) const = 0;		//Draw the figure
	virtual bool hasPoint(int x, int y) const  = 0 ;		//check whether fig contains point
	virtual string getFigData() const = 0;		//Get fig data

	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color

	//save and load functionality ///////////////////////////////////////////////////
	virtual void Save(ofstream& OutFile) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream& Infile) = 0;	//Load the figure parameters to the file
	////////////////////////////////////////////////////////////////////////////////////
	virtual std::string getShapeType() = 0;
	virtual std::string getColor() = 0;
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	//virtual void Rotate() = 0;	//Rotate the figure
	//virtual void Resize() = 0;	//Resize the figure
	//virtual void Move() = 0;		//Move the figure

	//virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	//virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};