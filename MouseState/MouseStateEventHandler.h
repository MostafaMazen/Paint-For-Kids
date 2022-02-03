#pragma once
#include<iostream>
#include<string>
#include "MouseStatesUtil.h"
#include "..\ApllicationManagerState\Header1.h"

class CFigure;

CFigure* returnFig(void* fig);
//C++ INTERFACE

class MouseEventHandler{

protected: 
    ApplicationInputStates mouseStPoint;
    public:
    virtual void onEvent(ApplicationInputStates& data) = 0;
    virtual ApplicationInputStates getMouseState() {
        return mouseStPoint;
    }


};


//class OnDown : public MouseEventHandler{
//
//private:
//   // fake instance *
//    ApplicationManagerState* appMngState;
//
//    public:
//        OnDown(ApplicationManagerState* appMngState):MouseEventHandler() {
//            this->appMngState = appMngState;
//        }
//        void onEvent(MouseStPoint data) {
//            mouseStPoint = data;
//            //cout << "DOWN coord: x=" << data.x << " y=" << data.y << endl;
//            if (appMngState->selectedShape != nullptr) {
//                this->appMngState->MouseOnDown = 1;
//            }
//        }
//
//};
//
//
//class OnMove : public MouseEventHandler{
//
//   private:
//       ApplicationManagerState* appMngState;
//       void* appManger;      
//    public:
//        OnMove(ApplicationManagerState* appMngState, void* appManger) :MouseEventHandler() {
//            this->appMngState = appMngState;
//            this->appManger = appManger;
//        }
//    void onEvent(MouseStPoint data){
//        mouseStPoint = data;
//        if (appMngState->selectedShape != nullptr) {
//            if (appMngState->MouseOnDown == 1) {
//                //cout << "MOVE coord: x=" << data.x << " y=" << data.y << " appMngr Add: " << appManger << endl;
//            }
//        }
//        /*this->appMngState->MouseXPOS = data.x;
//        this->appMngState->MouseYPOS = data.y;
//        this->appMngState->MouseOnMove = 1;*/
//    }
//    
//
//};
//
//
//class OnUp : public MouseEventHandler{
//    
//    private:
//    ApplicationManagerState* appMngState;
//    
//    public:
//        OnUp(ApplicationManagerState* appMngState) :MouseEventHandler() {
//            this->appMngState = appMngState;
//        }
//    void onEvent(MouseStPoint data){
//        mouseStPoint = data;
//        //cout << "Release coord: x=" << data.x << " y=" << data.y << endl;
//
//        this->appMngState->MouseOnDown = 0;
//    }
//
//};





