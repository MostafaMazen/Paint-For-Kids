#include "CEllipse.h"


CEllipse::CEllipse()
{
	sharedID++;
	ID = sharedID;
}

CEllipse::CEllipse(Point p1, Point p2, double StartAng, double EndAng, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	sharedID++;
	ID = sharedID;
	firstPoint = sFP = p1;
	secondPoint = sSP =  p2;

	StartAngle = StartAng;
	EndAngle = EndAng;
	xLength = p2.x - p1.x;
	yLength = p2.y - p1.y;

	startxLength = xLength;
	startyLength = yLength;

	factorPosition = 2;
}

void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawEllipse to draw Ellipse on the screen	
	pGUI->DrawEllipse(firstPoint, secondPoint, StartAngle, EndAngle,FigGfxInfo, Selected);


}

void CEllipse::setPoint(int x, int y)
{
	firstPoint.x = x;
	firstPoint.y = y;
}

Point CEllipse::getPoint()
{
	return firstPoint;
}

void CEllipse::setCenterPoint(int x, int y)
{
	if ((y - yLength / 2) <= 50) {
		return;
	}
	firstPoint.x = x - xLength/2;
	firstPoint.y = y - yLength/2;
	secondPoint.x = x + xLength/2;
	secondPoint.y = y + yLength/2;

	sFP = firstPoint;
	sSP = secondPoint;
}

void CEllipse::setSize(float factor)
{
	xLength = factor * startxLength;
	yLength = factor * startyLength;

	if (factor < 1) {
		firstPoint.x = sFP.x + xLength / 2;
		firstPoint.y = sFP.y + yLength / 2;
		secondPoint.x = sSP.x - xLength / 2;
		secondPoint.y = sSP.y - yLength / 2;
		return;
	}

	firstPoint.x = sFP.x - xLength / 2;
	firstPoint.y = sFP.y - yLength / 2;
	secondPoint.x = sSP.x + xLength / 2;
	secondPoint.y = sSP.y + yLength / 2;
}

bool CEllipse::hasPoint(int x, int y) const
{
	Point firstPoint = this->firstPoint;
	Point lastPoint = this->secondPoint;

	if ((firstPoint.x <= x && lastPoint.x >= x) && (firstPoint.y <= y && lastPoint.y >= y)) {
		return true;
	}
	return false;
}

string CEllipse::getFigData() const
{
	std::string figID = "FigID: " + std::to_string(ID);
	std::string figStartPoint = "TLPoint: (" + std::to_string(firstPoint.x) + ","
		+ std::to_string(firstPoint.y) + ")";
	std::string figEndPoint = "BRPoint: (" + std::to_string(secondPoint.x) + ","
		+ std::to_string(secondPoint.y) + ")";
	//std::string figArea = "Area: " + std::to_string(length * length);
	std::string figData = figID + " - " + figStartPoint + " - " + figEndPoint; //+ " - " + figArea; 
	return figData;
}


/////////////////////////////////////////save and load functionality /////////////////////
void CEllipse::Save(ofstream& myFile) {
	myFile << "Ellipse" << "\t"
		<< this->ID << "\t"
		<< this->firstPoint.x << "\t"
		<< this->firstPoint.y << "\t"
		<< this->secondPoint.x << "\t"
		<< this->secondPoint.y << "\t"
		<< this->StartAngle << "\t"
		<< this->EndAngle << "\t"
		<< this->FigGfxInfo.DrawClr.toHexa() << "\t";

	if (this->FigGfxInfo.isFilled) {
		myFile << FigGfxInfo.FillClr.toHexa() << "\n";
	}
	else {
		myFile << "NOTFILLED" << "\n";
	}
}

void CEllipse::Load(ifstream& myFile) {
	int id;
	double sAngle, eAngle;
	string strDrwClr, strFillClr;
	Point fPoint;
	Point sPoint;
	char* drwClr;
	char* fillClr;

	myFile >> id >> fPoint.x >> fPoint.y >> sPoint.x >> sPoint.y >> sAngle >> eAngle >> strDrwClr >> strFillClr;

	// manual casting
	drwClr = &strDrwClr[0];
	fillClr = &strFillClr[0];
	this->firstPoint = fPoint;
	this->secondPoint = sPoint;
	this->StartAngle = sAngle;
	this->EndAngle = eAngle;

	sFP = firstPoint;
	sSP = secondPoint;

	xLength = secondPoint.x - firstPoint.x;
	yLength = secondPoint.y - firstPoint.y;

	startxLength = xLength;
	startyLength = yLength;


	cout << "==============" << endl;
	cout << strDrwClr << endl;
	cout << fillClr << endl;



	color savedColor;
	int r, g, b;
	savedColor.hexToRGB(drwClr, r, g, b);
	ChngDrawClr(color(r, g, b));
	FigGfxInfo.BorderWdth = UI.PenWidth;
	Selected = false;

	if (strFillClr == "NOTFILLED") {
		FigGfxInfo.isFilled = false;
		cout << "===im not filled==" << endl;
	}
	else {
		savedColor.hexToRGB(fillClr, r, g, b);
		ChngFillClr(color(r, g, b));
	}

}

std::string CEllipse::getShapeType()
{
	return "ELLIPSE";
}

std::string CEllipse::getColor()
{
	return this->FigGfxInfo.FillClr.toHexa();
}