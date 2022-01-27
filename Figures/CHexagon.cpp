#include "CHexagon.h"
#include "iostream"
#include <math.h> 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
CHexagon::CHexagon(Point _center, int _raduis, int* _pX, int* _pY, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	pX = _pX;
	pY = _pY;
	center = _center;
	raduis = _raduis;
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
	//length = factor * startLength;
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

void CHexagon::Save(ofstream& OutFile)
{
}

void CHexagon::Load(ifstream& Infile)
{
}
