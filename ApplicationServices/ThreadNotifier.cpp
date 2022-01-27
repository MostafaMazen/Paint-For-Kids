#include"ThreadNotifier.h"

//later on we can change this pattern 
//rathar than we use this string messages we can use something else like 
//struct 


void ThreadNotifier::on(std::string topic, ThreadEventsHandler*  handler)
{
	
	if (!this->events[topic].empty()) {
		
		events[topic].pop_back();
		this->events[topic].push_back(handler);
	
	}
	else {
		this->events[topic].push_back(handler);
	}
}

void ThreadNotifier::off(std::string topic) {
	if (!this->events[topic].empty()) {
		this->events[topic].pop_back(); // unregister me 
	}
}

void ThreadNotifier::emit(std::string topic, PanelListener* panelListen) {
	//std::cout<<"emitted .... !"<<std::endl;
	if (!this->events[topic].empty()) {
		//std::cout << "Calling every body!!!!!!!!!!!!!!!!!!" << std::endl;
		this->events[topic][0]->onMessageRecieved(panelListen);
	}

	//for (int i = 0; i < events[topic].size(); i++) {
	//	//error prone area if FIX AFTER DEBUG
	//	events[topic][i]->onMessageRecieved(appPanelMngr);
	//}
}
