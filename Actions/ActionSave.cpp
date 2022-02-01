#include "ActionSave.h"
#include"..\ApplicationManager.h"
#include<fstream>
#include<string>
#include"..\GUI\UI_Info.h"


ActionSave::ActionSave(ApplicationManager* pApp, int FigCount) :Action(pApp) {
	figCount = FigCount;
	myFileName = "figsFile";
}

void ActionSave::Execute() {
	

	GUI* pGUI = pManager->GetGUI();
	// pGUI->PrintMessage("write file name then press ENTER : ");
	// something should happen here to get file name from statusbar to
	// put it in myFileName instead of test

	std::string fileSaved = pManager->saveFile(pGUI->pWind->getWindow());
	if (fileSaved == "") {
		return;
	}
	ofstream myFile;
	string fileFormat = fileSaved.substr(fileSaved.length()-3);
	if (fileFormat == "txt") {
		myFile.open(fileSaved, ios::trunc | ios::out);
	}
	else {
		myFile.open(fileSaved + ".txt", ios::trunc | ios::out);
	}
	
	

	//here we should save 
	//pGUI.DrawColor
	//pGUI.FillColor
	//pGUI.BkGrndColor
	myFile << pGUI->getCrntDrawColor().toHexa()<<"\t"
		   << pGUI->getCrntFillColor().toHexa() << "\t"
		   << pGUI->getCrntBackgroundColor().toHexa() << "\n"
		   << figCount << "\n";
		//cout << pGUI->getCrntBackgroundColor().toHexa() << "*******" << endl;
	
	pManager->SaveFigs(myFile);  //Saving each figure in the stack 

	myFile.close();
	pGUI->PrintMessage("file saved ");


}

void ActionSave::Undo()
{
}

void ActionSave::Redo()
{
}
