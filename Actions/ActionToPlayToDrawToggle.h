#pragma once

#include "Action.h"
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

class ActionToPlayDrawToggle :public Action
{
	private:
		ApplicationManager* appMngr;
	public:
		ActionToPlayDrawToggle(ApplicationManager* pApp);
		virtual void Execute();

		virtual void Undo();

		virtual void Redo();
};