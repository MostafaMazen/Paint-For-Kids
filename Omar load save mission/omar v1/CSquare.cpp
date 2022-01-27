#include "CSquare.h"
#include<fstream>
#include<string>

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	
	TopLeftCorner = P1;
	length = len;
	
}
CSquare::CSquare(){}//====>omar

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
}

void CSquare::Save(ofstream& myFile) {
	myFile << "Square" << "\t"
		<< this->ID << "\t"
		<< this->TopLeftCorner.x << "\t"
		<< this->TopLeftCorner.y << "\t"
		<< this->length << "\t"
		<< this->FigGfxInfo.DrawClr.toHexa() << "\t";
		
	if (this->FigGfxInfo.isFilled) {
		myFile << FigGfxInfo.FillClr.toHexa()<<"\n";
	}
	else {
		myFile <<"NOTFILLED" << "\n";
	}
}

void CSquare::Load(ifstream& myFile) {
	int id,len;
	string strDrwClr, strFillClr;
	Point topleft;
	char* drwClr;
	char* fillClr;

	myFile >> id >> topleft.x >>topleft.y >> length>> strDrwClr>> strFillClr;
	//manual casting
	drwClr = &strDrwClr[0];
	fillClr = &strFillClr[0];
	this->TopLeftCorner = topleft;
	cout << "=============="<<endl;
	cout << strDrwClr<<endl;
	cout << fillClr << endl;

	
	
	color savedColor;
	int r, g, b;
	savedColor.hexToRGB(drwClr,r,g,b);
	ChngDrawClr(color(r, g, b));
	FigGfxInfo.BorderWdth = UI.PenWidth;
	Selected = false;

	if (strFillClr == "NOTFILLED") {
		FigGfxInfo.isFilled = false;
			cout << "===im not filled=="<<endl;
	}
	else {
		savedColor.hexToRGB(fillClr, r, g, b);
		ChngFillClr(color(r, g, b));
	}
	
	
	
}
