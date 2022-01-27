#include "CEllipse.h"

CEllipse::CEllipse(Point p1, Point p2, double StartAng, double EndAng, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
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
	firstPoint.x = x - xLength/2;
	firstPoint.y = y - yLength/2;
	secondPoint.x = x + xLength/2;
	secondPoint.y = y + yLength/2;
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

void CEllipse::Save(ofstream& OutFile)
{
}

void CEllipse::Load(ifstream& Infile)
{
}
