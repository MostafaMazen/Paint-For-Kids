#pragma once
#include<iostream>
#include<string>
#include "MouseStatesUtil.h"
#include "..\ApllicationManagerState\Header1.h"

class CFigure;

CFigure* returnFig(void* fig);

//C++ INTERFACE
class WindowStateHandler{

protected: 
    ApplicationInputStates mouseStPoint;
    public:
    virtual void onEvent(ApplicationInputStates& data) = 0;
    virtual ApplicationInputStates getMouseState() {
        return mouseStPoint;
    }


};






