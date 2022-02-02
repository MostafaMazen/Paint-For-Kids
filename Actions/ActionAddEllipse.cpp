#include "ActionAddEllipse.h"
#include "..\Figures\CEllipse.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddEllipse::ActionAddEllipse(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddEllipse::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo EllGfxInfo;
	EllGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	EllGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	EllGfxInfo.FillClr = pGUI->getCrntFillColor();
	if (EllGfxInfo.FillClr.toHexa() != "#000000") {
		EllGfxInfo.isFilled = true;
	}
	EllGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	// Read Ellipse data from the user

	pGUI->PrintMessage("New Ellipse: Click at first point");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	pGUI->PrintMessage("New Ellipse: Click at second point");
	//Read 2nd point and store in point P2
	pGUI->GetPointClicked(P2.x, P2.y);
	pGUI->ClearStatusBar();


	double StartAngle = 0;
	double EndAngle=360;
	CEllipse* R = new CEllipse(P1,P2,StartAngle,EndAngle, EllGfxInfo);
	pManager->AddFigure(R);
}

void ActionAddEllipse::Undo()
{
}

void ActionAddEllipse::Redo()
{
}
