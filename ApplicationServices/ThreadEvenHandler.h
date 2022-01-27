#pragma once

struct PanelListener;

class ThreadEventsHandler{

    public:
    virtual void onMessageRecieved(PanelListener* panelListen) = 0;


};