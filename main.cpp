#include "ApplicationManager.h"
#include<thread>
#include <future>
#include<iostream>
#include "ApplicationFiguresHelperPanel\ApplicationFiguresHelperPanel.h"

class ThreadNotifier;


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
	
	ThreadNotifier threadNoti;
	cout << "From Main: " << &threadNoti << std::endl;
	cout <<"From Main ThreeadID: "<< this_thread::get_id() << std::endl;
	auto appManagerThread = runAppManagerThread(&threadNoti); // waiting for arguments
	auto panalThread = runPanalThread(&threadNoti); // waiting for arguments

	std::cout << "watch" << std::endl;

	return 0;
}

