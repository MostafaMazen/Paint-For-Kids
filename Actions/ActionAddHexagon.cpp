#include "ActionAddHexagon.h"
#include "..\Figures\CHexagon.h"
#include <iostream>
#include <cstdio>
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <math.h> 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
ActionAddHexagon::ActionAddHexagon(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddHexagon::Execute()
{
	int n = 6;
	int* pX = new int[n];
	int* pY = new int[n];
	int r;
	Point center;
	Point refPoint;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo SqrGfxInfo;
	SqrGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	if (SqrGfxInfo.FillClr.toHexa() != "#000000") {
		SqrGfxInfo.isFilled = true;
	}
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();
	//center
	pGUI->PrintMessage("New Hexagon: Center point");
	pGUI->GetPointClicked(center.x, center.y);
	//refpoint
	pGUI->PrintMessage("click point to calculate the raduis");
	pGUI->GetPointClicked(refPoint.x, refPoint.y);
	// 
	r = ((center.x - refPoint.x) ^ 2 + (center.y - refPoint.y) ^ 2) ^ (1 / 2);
	for (int i = 0; i < n; i++) {
		pX[i] = center.x + r * cos(2 * M_PI * i / n);
		pY[i] = center.y + r * sin(2 * M_PI * i / n);
		//cout << pX[i] << " , " << pY[i] << endl;
	}

	pGUI->ClearStatusBar();
	CHexagon* R = new CHexagon(center, r, pX, pY, SqrGfxInfo);

	pManager->AddFigure(R);
}

void ActionAddHexagon::Undo()
{
}

void ActionAddHexagon::Redo()
{
}
