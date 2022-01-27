#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;
public:
	CSquare(Point , int, GfxInfo FigureGfxInfo);
	CSquare();//to use in load ==>>by omar
	virtual void DrawMe(GUI* pOut) const;
	virtual void Save(ofstream& file);
	virtual void Load(ifstream& file);
};

#endif