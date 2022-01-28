#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"
#include <fstream>

class CSquare : public CFigure
{
private:		
	Point TopLeftCorner;	
	int length;
	int startLength;

public:
	CSquare();
	CSquare(Point , int, GfxInfo FigureGfxInfo );
	void setPoint(int x, int y);
	virtual Point getPoint();
	virtual void setCenterPoint(int x, int y);
	virtual void setSize(float factor);
	virtual void DrawMe(GUI* pOut) const;
	virtual bool hasPoint(int x,int y) const;
	virtual string getFigData() const;
	virtual void Save(ofstream& OutFile);	//Save the figure parameters to the file
	virtual void Load(ifstream& Infile);	//Load the figure parameters to the file
	virtual std::string getShapeType();
	virtual std::string getColor();

};

#endif