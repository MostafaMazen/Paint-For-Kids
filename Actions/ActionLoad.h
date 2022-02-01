#pragma once

#include "Action.h"
#include<string>

class ActionLoad :public Action 
{
private:
	string myFileName;
public:
	ActionLoad(ApplicationManager* pApp);
	virtual void Execute();

	virtual void Undo();

	virtual void Redo();

};