#pragma once

#include "Action.h"
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

class ActionToPlayDrawToggle :public Action
{
public:
	ActionToPlayDrawToggle(ApplicationManager* pApp);
	virtual void Execute();
};