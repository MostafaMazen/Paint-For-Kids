#pragma once

//DEPENDENCIES 
#include<iostream>
#include<map>
#include<vector>
#include<string>
#include"MouseStateEventHandler.h"
#include "MouseStatesUtil.h"

//~this Notifier JOBS : 
//![listen on Type VM_BUTTONDOWN]
//! IF button is DOWN .. notify listeners that state is DOWN
//! IF BUTTON IS MOVE .. notify listeners that the state is MOVE
//! ELSE THE Notifier can understand what the last state is !  
//! WINDOW CAN NOTIFY ME THAT THE CURRENT STATE MOVE OR DOWN ! ? 

//~[needs]
  //* class Reperesent the eventHandler 


class ApplicationWindowState{

    public:
    
    ApplicationWindowState(){
        //done
    }

    //to be able to notify u should implement this function 

    void on(std::string topic, WindowStateHandler* handler) {
        //TODO FIX IF ERROR APPEAR => error prone area
        //~ subscribe on something if it's already subscribed don't add handles again 
        //~ search on handler if it lives inside or not ! 
        if(!events[topic].empty()){
            return; //force each topic to contain only one handler 
        }else{
            events[topic].push_back(handler);
        }
    };

    void off(std::string topic , WindowStateHandler* handler){
        if(!events[topic].empty()){
            events[topic].pop_back();
        }
    }

    void emit(std::string topic , ApplicationInputStates& data){
        for(int i = 0 ; i < events[topic].size();i++){
            //error prone area if FIX AFTER DEBUG
            events[topic][i]->onEvent(data);
        }
    }
    
    private:

        std::map<std::string,std::vector<WindowStateHandler*>>events;

};