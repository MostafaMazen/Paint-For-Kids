#pragma once

#include "Action.h"
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

class ActionToPlay :public Action
{
public:
	ActionToPlay(ApplicationManager* pApp);
	virtual void Execute();
};