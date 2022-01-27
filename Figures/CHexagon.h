#ifndef CHEXAGON_H
#define CHEXAGON_H

#include "CFigure.h"

class CHexagon : public CFigure
{
private:
	int* pX;
	int* pY;
	int raduis, startR;
	Point center;
public:
	CHexagon(Point _center, int _raduis, int* _pX, int* _pY, GfxInfo FigureGfxInfo);
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