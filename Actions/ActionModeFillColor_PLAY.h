#pragma once
#include"Action.h"

class ActionModeFillColor : public Action {

public:
	ActionModeFillColor(ApplicationManager* appMngr);
	virtual void Execute();

	virtual void Undo();

	virtual void Redo();

};