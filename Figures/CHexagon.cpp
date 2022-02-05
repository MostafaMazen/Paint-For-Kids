#include "CHexagon.h"
#include "iostream"
#include <math.h> 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void CHexagon::SavePoints(ofstream& OutFile)
{
	
	for (int i = 0; i < 6; i++) {
		OutFile << pX[i]<<"\t";
		OutFile << pY[i]<<"\t";
	}
}
CHexagon::CHexagon()
{
	sharedID++;
	ID = sharedID;
}
CHexagon::CHexagon(Point _center, int _raduis, int* _pX, int* _pY, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	sharedID++;
	ID = sharedID;
	pX = _pX;
	pY = _pY;
	center = _center;
	raduis = startR = _raduis;
	factorPosition = 2;
}

CHexagon::~CHexagon()
{
		delete [] pX;
		delete [] pY;
}



void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawHexagon(pX,pY, FigGfxInfo, Selected);
}

void CHexagon::setPoint(int x, int y)
{
	/*firstPoint.x = x;
	firstPoint.y = y;*/
}

Point CHexagon::getPoint()
{
	Point p;
	return p;
}

void CHexagon::setCenterPoint(int x, int y)
{
	if (y - raduis <= 50) {
		return;
	}
	center.x = x;
	center.y = y;
	for (int i = 0; i < 6; i++) {
		pX[i] = center.x + raduis * cos(2 * M_PI * i / 6);
		pY[i] = center.y + raduis * sin(2 * M_PI * i / 6);
		//cout << pX[i] << " , " << pY[i] << endl;
	}
}


void CHexagon::setSize(float factor)
{
	// change radius acoording to size
	raduis = factor * startR;

	for (int i = 0; i < 6; i++) {
		pX[i] = center.x + raduis * cos(2 * M_PI * i / 6);
		pY[i] = center.y + raduis * sin(2 * M_PI * i / 6);
		//cout << pX[i] << " , " << pY[i] << endl;
	}
}

bool CHexagon::hasPoint(int x, int y) const
{
	//  int    polyCorners  =  how many corners the polygon has
//  int  pX[]      =  horizontal coordinates of corners
//  int  pY[]      =  vertical coordinates of corners
//  int  x, y         =  point to be tested
//
//
//  The function will return YES if the point x,y is inside the polygon, or
//  NO if it is not.  If the point is exactly on the edge of the polygon,
//  then the function may return YES or NO.
//
//  Note that division by zero is avoided because the division is protected
//  by the "if" clause which surrounds it.
	int polyCorners = 6;
	int   i, j = polyCorners - 1;
	bool  oddNodes = false;
	for (i = 0; i < polyCorners; i++) {
		if ((pY[i] < y && pY[j] >= y
			|| pY[j] < y && pY[i] >= y)
			&& (pX[i] <= x || pX[j] <= x)) {
			oddNodes ^= (pX[i] + (y - pY[i]) / (pY[j] - pY[i]) * (pX[j] - pX[i]) < x);
		}
		j = i;
	}
	//getFigData();
	return oddNodes;
}



string CHexagon::getFigData() const
{
	std::string figID = "FigID: " + std::to_string(ID);
	std::string centerPoint = "center Point: (" + std::to_string(center.x) + ","
		+ std::to_string(center.y) + ")";
	float area = abs(((sqrt(3) * 3) / 2) * (raduis ^ 2));
	std::string areaAsString = "Area: " + std::to_string(area);
	std::string figData = figID + " - " + centerPoint + " - " + areaAsString; //+ " - " + figArea;
	return figData;
}

/////////////////////////////////////////save and load functionality /////////////////////
void CHexagon::Save(ofstream& myFile) {
	myFile << "Hexagon" << "\t"
		<< this->ID << "\t"
		<< this->center.x << "\t"
		<< this->center.y << "\t"
		<< this->raduis << "\t";
	SavePoints(myFile);
	myFile<< this->FigGfxInfo.DrawClr.toHexa() << "\t";

	if (this->FigGfxInfo.isFilled) {
		myFile << FigGfxInfo.FillClr.toHexa() << "\n";
	}
	else {
		myFile << "NOTFILLED" << "\n";
	}
}

void CHexagon::Load(ifstream& myFile) {

	pX = new int[6];
	pY = new int[6];

	int id,x,y;
	string strDrwClr, strFillClr;
	char* drwClr;
	char* fillClr;

	myFile >> id >> center.x >> center.y >> raduis;
	startR = raduis;
	for (int i = 0; i < 6; i++) {
		myFile >> x >> y;
		pX[i] = x;
		pY[i] = y;
	}
	myFile >> strDrwClr >> strFillClr;
	// manual casting
	drwClr = &strDrwClr[0];
	fillClr = &strFillClr[0];

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

std::string CHexagon::getShapeType()
{
	return "HEXAGON";
}

std::string CHexagon::getColor()
{
	return this->FigGfxInfo.FillClr.toHexa();
}
