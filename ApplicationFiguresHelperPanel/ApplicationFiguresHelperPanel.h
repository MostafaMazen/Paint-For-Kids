#pragma once
#include<thread>
#include<future>
#include "..\ApplicationObjectHelperTool\ApplicationObjectHelperTool.h"
#include "..\ApplicationServices\ThreadNotifier.h"


//this Application IS subject can emmit data to others if they are listeners 
class ApplicationFiguresHelperPanelManager{

    public:

    ApplicationFiguresHelperPanelManager(ThreadNotifier* threadNoti);

    ~ApplicationFiguresHelperPanelManager();

    void launchPanal(); //remember to launch this panal using depenency injection on function object later

    void onInit();
    void onClose();
    private:
        ThreadNotifier* threadNoti;
        ApplicationObjectHelperTool* helperTool;
	//helperTool.init();
};
