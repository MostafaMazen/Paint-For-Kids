#include "ApplicationFiguresHelperPanel.h"

ApplicationFiguresHelperPanelManager::ApplicationFiguresHelperPanelManager(ThreadNotifier* threadNoti)
{
    this->threadNoti = threadNoti;
    std::cout << "From PanelMngr: " << threadNoti << std::endl;
    std::cout << "From PanelMngr ThreadID: " << std::this_thread::get_id() << std::endl;
    this->helperTool = new ApplicationObjectHelperTool(); // on the heap
   
}

ApplicationFiguresHelperPanelManager::~ApplicationFiguresHelperPanelManager()
{
    delete helperTool;
    this->helperTool = nullptr;
}

void ApplicationFiguresHelperPanelManager::launchPanal()
{
    //if one thread already called me that's mean i can't block anythreads 
    this->helperTool->init(this->threadNoti);
}

void ApplicationFiguresHelperPanelManager::onInit()
{     
        //std::cout<<"emitting state"<<std::endl;
        PanelListener* pl = new PanelListener();
        pl->appPanelMngr = this;
        pl->stat = PANEL_OPEN;
        std::async(std::launch::async, [this,&pl]() {
            threadNoti->emit("PANEL_START", pl);
            });
}

void ApplicationFiguresHelperPanelManager::onClose() {
    //this->helperTool->close();
}


