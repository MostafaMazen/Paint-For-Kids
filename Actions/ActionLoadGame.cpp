#include "ActionLoadGame.h"
#include<fstream>
#include "../Figures/CFigure.h"
#include "../Figures/CSquare.h"
#include "../Figures/CEllipse.h"
#include "../Figures/CHexagon.h"
#include "../CMUgraphicsLib/colors.h"
#include"..\ApplicationManager.h"


ActionLoadGame::ActionLoadGame(ApplicationManager* pApp) :Action(pApp)
{
	GameFileName = "GameFile.txt";
	//GameFileName = "f1.txt";
}

void ActionLoadGame::Execute() {
	GUI* pGUI = pManager->GetGUI();
	//here u clear screen and remove old figs  
	//first cause it's important to not dublicate figs when save again 
	
	std::cout << GameFileName << std::endl;
	pGUI->ClearDrawArea();
	pManager->RemoveAllFigs();

	ifstream myFile;
	char* drwClr;
	char* backClr;
	char* fillClr;
	string strDrwClr,strFillClr, strBackClr;
	string figuerName;
	int figsCount;
	CFigure* oldFig;
	
	myFile.open(GameFileName);
	myFile >> strDrwClr >>strFillClr>> strBackClr;
	int r, g, b;
	color savedColor;
	//this manual casting
	//is importants cause function take only pointer char when fstream retrive string
	drwClr = &strDrwClr[0];
	fillClr = &strFillClr[0];
	backClr = &strBackClr[0];


	
	// use set brush from window objct 
	savedColor.hexToRGB(drwClr, r, g, b);
	UI.DrawColor = color(r,g,b);
	//
	savedColor.hexToRGB(fillClr, r, g, b);
	UI.FillColor = color(r, g, b);
	//
	savedColor.hexToRGB(backClr, r, g, b);
	UI.BkGrndColor = color(r, g, b);

	
	
	myFile >> figsCount;
	cout << strDrwClr << "============"<<endl;
	cout << strFillClr << endl;
	cout << strBackClr << endl;
	cout << figsCount << endl;

	std::async(std::launch::async, [this,&figsCount,&myFile,&figuerName,&oldFig,&pGUI]() {
		//!ERROR PRONE AREA	
		while (figsCount)            //for each line on the file we will read it and determine its type
		{
			myFile >> figuerName;
			if (figuerName == "Square")
				oldFig = new CSquare;
			else if (figuerName == "Ellipse")
				oldFig = new CEllipse;
			else if (figuerName == "Hexagon")
				oldFig = new CHexagon;

			oldFig->Load(myFile);
			pManager->AddFigure(oldFig);
			figsCount--;

		}
		pManager->UpdateInterface();
		pGUI->PrintMessage("file Loaded ");
		});

}

void ActionLoadGame::Undo()
{
}

void ActionLoadGame::Redo()
{
}
