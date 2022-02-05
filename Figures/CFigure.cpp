#include "CFigure.h"

int CFigure::sharedID = 0;

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
}

CFigure::CFigure()
{
	ID++;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected == false ? false : true; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr;
}

std::string CFigure::getShapeType()
{
	return "PARENT_SHAPE";
}

CFigure* returnFig(void* fig) {
	return (CFigure*)fig;
}
