#ifndef CELLIPSE_H
#define CELLIPSE_H

#include "CFigure.h"

class CEllipse : public CFigure
{
private:
	Point firstPoint;
	Point secondPoint;
	Point sFP, sSP;
	double  StartAngle;
	double  EndAngle;
	int xLength, yLength;
	int startxLength, startyLength;
public:
	//CEllipse(Point,Point,double,double, GfxInfo FigureGfxInfo);
	CEllipse(Point P1, Point p2, double StartAng, double EndAng, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
	void setPoint(int x, int y);
	virtual Point getPoint();
	virtual void setCenterPoint(int x, int y);
	virtual void setSize(float factor);
	virtual bool hasPoint(int x, int y) const;
	virtual string getFigData() const;
	virtual void Save(ofstream& OutFile);	//Save the figure parameters to the file
	virtual void Load(ifstream& Infile);	//Load the figure parameters to the file

};

#endif
