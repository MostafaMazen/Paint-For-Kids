#include "ApplicationManager.h"
#include "GUI\GUI.h"
#include<thread>
#include <future>
#include<iostream>
#include "ApplicationFiguresHelperPanel\ApplicationFiguresHelperPanel.h"

class ThreadNotifier;


//agenda will be here 
//we need to manage on select show panal 
//we need to inject our ui into application manager
//we need to assign the application manager on select show the menu 
//we need to let the application manager create a new thread fro this async 
//then we need to  create a bridge channel between the application manager and the control panal
//we wanna deliver this information to the figures via the application manager

//[aim] panalManager sent through Evenet Channel to Another 
//thread carrying ApplicationManager // callback or handler // implement handler interface


//23-1-2021 we need to manage the switch mode to the game ! 
//plan to switch to the game 
//code first 




class RUNpanalThread: public ThreadEventsHandler {

	bool close;
	public:

	RUNpanalThread(ThreadNotifier* threadNoti){
		close = false;
		this->threadNoti  = threadNoti;
	}

	void onMessageRecieved(PanelListener* panelListen)
	{
		if (panelListen->threadClose == true) {
			close = true;
			panal->onClose();
		}
	}

	void operator()(){
		//do nothing for now
		this->threadNoti->on("THREAD_CLOSE", this);
		this->panal = new ApplicationFiguresHelperPanelManager(threadNoti);
		while(1){
			if (close == true) {
				break;
			}
			this->panal->onInit();
			std::this_thread::sleep_for(2ms);
		}
		
		//this->panal->launchPanal();
	}

	private:
	ThreadNotifier* threadNoti;
	ApplicationFiguresHelperPanelManager* panal;
	
};


class RUNappManagerThread{

	public:

	RUNappManagerThread(ThreadNotifier* threadNoti){
		this->threadNoti  = threadNoti;
	
	}

	
	void operator()(){
		//do nothing for now
		this->appMngr = new ApplicationManager(threadNoti);
		this->appMngr->Run();
	}

	private:
	ThreadNotifier* threadNoti;
	ApplicationManager* appMngr;
	
};


std::future<void>runPanalThread(ThreadNotifier* threadNoti){
	return std::async(std::launch::async,RUNpanalThread{threadNoti});
}


std::future<void>runAppManagerThread(ThreadNotifier* threadNoti){
	return std::async(std::launch::async,RUNappManagerThread{threadNoti});
}









int main()
{
	/*
	GUI* g=new GUI();
	
	
	window* w=g->CreateWind(200, 300, 10, 10);
	int x, y;
	w->WaitMouseClick(x, y);
	*/
	
	ThreadNotifier* threadNoti = new ThreadNotifier();
	cout << "From Main: " << threadNoti << std::endl;
	cout <<"From Main ThreeadID: "<< this_thread::get_id() << std::endl;
	auto appManagerThread = runAppManagerThread(threadNoti); // waiting for arguments
	auto panalThread = runPanalThread(threadNoti); // waiting for arguments

	std::cout << "watch" << std::endl;

	return 0;
}

