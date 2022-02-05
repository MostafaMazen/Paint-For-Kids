#include "CSquare.h"




CSquare::CSquare()
{
	sharedID++;
	ID = sharedID;
}


CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	sharedID++;
	ID = sharedID;
	TopLeftCorner = P1;
	int x = (TopLeftCorner.x - (TopLeftCorner.x + length)) / 2;
	int y = (TopLeftCorner.y - (TopLeftCorner.y + length)) / 2;
	//setCenterPoint(x, y);
	length = len;
	startLength = length;
	//factorPosition = 2;
}

void CSquare::setPoint(int x, int y)
{
	TopLeftCorner.x = x;
	TopLeftCorner.y = y;
}

Point CSquare::getPoint()
{
	return TopLeftCorner;
}

void CSquare::setCenterPoint(int x, int y)
{
	/*center.x = x;
	center.y = y;*/
	if (y - (length / 2) <= 50) {
		return;
	}
	TopLeftCorner.x = x - (length/2);
	TopLeftCorner.y = y - (length/2);
}

void CSquare::setSize(float factor)
{
	length = factor*startLength;
}
	

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
	

}

bool CSquare::hasPoint(int x, int y) const
{
	Point firstPoint = this->TopLeftCorner;
	Point lastPoint;
	lastPoint.x = firstPoint.x + this->length;
	lastPoint.y = firstPoint.y + this->length;

	if ((firstPoint.x <= x && lastPoint.x >= x) && (firstPoint.y <= y && lastPoint.y >= y)) {
		return true;
	}
	return false;
}

string CSquare::getFigData() const
{
	std::string figID = "FigID: " + std::to_string(ID);
	std::string figStartPoint = "TLPoint: (" + std::to_string(TopLeftCorner.x)+","
								+ std::to_string(TopLeftCorner.y) + ")";
	std::string figEndPoint = "BRPoint: (" + std::to_string(TopLeftCorner.x+length) + ","
		+ std::to_string(TopLeftCorner.y+length) + ")";
	std::string figArea = "Area: " + std::to_string(length * length);
	std::string figData = figID + " - " + figStartPoint + " - " + figEndPoint + " - " + figArea; //figID + " - " +
	return figData;
}

/////////////////////////////////////////save and load functionality /////////////////////

void CSquare::Save(ofstream& myFile) {
	myFile << "Square" << "\t"
		<< this->ID << "\t"
		<< this->TopLeftCorner.x << "\t"
		<< this->TopLeftCorner.y << "\t"
		<< this->length << "\t"
		<< this->FigGfxInfo.DrawClr.toHexa() << "\t";

	if (this->FigGfxInfo.isFilled) {
		myFile << FigGfxInfo.FillClr.toHexa() << "\n";
	}
	else {
		myFile << "NOTFILLED" << "\n";
	}
}

void CSquare::Load(ifstream& myFile) {
	int id, len;
	string strDrwClr, strFillClr;
	Point topleft;
	char* drwClr;
	char* fillClr;

	myFile >> id >> topleft.x >> topleft.y >> length >> strDrwClr >> strFillClr;

	startLength = length;

	//manual casting
	drwClr = &strDrwClr[0];
	fillClr = &strFillClr[0];
	this->TopLeftCorner = topleft;
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

std::string CSquare::getShapeType()
{
	return "SQUARE";
}

std::string CSquare::getColor()
{
	return this->FigGfxInfo.FillClr.toHexa();
}

/////////////////////////////////////////////////////////////////////////////////////////