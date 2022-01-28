#ifndef CHEXAGON_H
#define CHEXAGON_H

#include "CFigure.h"
#include <fstream>

class CHexagon : public CFigure
{
private:
	int* pX;
	int* pY;
	int raduis, startR;
	Point center;
	static std::string SHAPE_TYPE;

	void SavePoints(ofstream& OutFile);    // saving points async non-blocking
public:
	CHexagon();
	CHexagon(Point _center, int _raduis, int* _pX, int* _pY, GfxInfo FigureGfxInfo);
	~CHexagon();
	virtual void DrawMe(GUI* pOut) const;
	void setPoint(int x, int y);
	virtual Point getPoint();
	virtual void setCenterPoint(int x, int y);
	virtual void setSize(float factor);
	virtual bool hasPoint(int x, int y) const;
	virtual string getFigData() const;
	virtual void Save(ofstream& OutFile);	//Save the figure parameters to the file
	virtual void Load(ifstream& Infile);	//Load the figure parameters to the file
	virtual std::string getShapeType();
	virtual std::string getColor();

};

#endif