#include "ApplicationManager.h"
#include "GUI\GUI.h"
#include<thread>
#include <future>
#include<iostream>
#include "ApplicationFiguresHelperPanel\ApplicationFiguresHelperPanel.h"

class ThreadNotifier;

//::NEW AGENDA FRIDAY::
/*
	Planning the game : 
	1- what i need ?  i need when i click on the switch button a new menu get generate ! 
	2- load the gameFile.text to the drawing area with new functionalty 
	3- allow the child or the user to pick mode before touch the board 
	4- after picking the mod that he will follow allow him to pick the first shape [CFigure] from all the figs on the screen 
	5- make this fig gisappear then allow him to pick another figs according to the mode that he already has picked ! 
	6- if he picked well we will add the correct to a counter or something else we will add falsy picks to another counter 
	7- after trying [don't know yet if it will be infinte or number of tries ?] 
	8- display all those result to him using panal or the screen or whatever 
	9- ask the user to replay or back to the draw mode 
	10- if the user picked to back to the drawing mode i should clear the whole screen and back to the draw normally 
	11- if he picked to replay again the game we will have to clear the screen and let him back again to the start point 

	::::::[game states]:::::

	GAME MODE: ON->START 
	1- drawing area cleared  maybe if we used load it will clear the screen and load up the new files ! ?  yeah ia m sure 
	2- new drawing tool bar 
	3- all the menu buttons working fine 


	::URGENT FIXING THE POINTERS 

	::tool bar :  [fixed] 
	

*/




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

