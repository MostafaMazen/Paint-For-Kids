#pragma once
#include"Action.h"




class ActionModeFigType : public Action {

public:
	ActionModeFigType(ApplicationManager* appMngr);
	virtual void Execute();

	virtual void Undo();

	virtual void Redo();

};





