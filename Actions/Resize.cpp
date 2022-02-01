#include "Resize.h"

Resize::Resize(ApplicationManager* pAppMgr, CFigure* selected) :Action(pAppMgr), FigureSelected(selected)
{
	FigureSelected = selected;
}


void Resize::Execute()
{
    
    float factor = 1;
	if (FigureSelected->factorPosition + 1 == 5) {
        FigureSelected->factorPosition = -1;
	}
    ResizeFactor RF = ResizeFactor(++(FigureSelected->factorPosition));
    switch (RF)
    {
    case QUARTER:
        factor =  0.25;
        break;
    case HALF:
        factor = 0.5;
        break;
    case NORMAL:
        factor = 1;
        break;
    case TWOTIMES:
        factor = 2;
        break;
    case FOURTIMES:
        factor = 4;
        break;
    }

	FigureSelected->setSize(factor);
}

void Resize::Undo()
{
}

void Resize::Redo()
{
}
