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

	std::string fileSaved = pManager->saveFile(pGUI->pWind->getCurrentWindow());
	if (fileSaved == "") {
		return;
	}
	ofstream myFile;
	myFile.open(fileSaved + ".txt", ios::out);
	

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