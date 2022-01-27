#include"ApplicationServices.h"


//later on we can change this pattern 
//rathar than we use this string messages we can use something else like 
//struct 

void ApplicationNotifierService::on(std::string topic, void(*callback)(std::string)) {

	if (!this->events[topic].empty()) {
		return;
	}
	else {
		this->events[topic].push_back(callback);
	}
}


void ApplicationNotifierService::off(std::string topic) {
	if (!this->events[topic].empty()) {
		this->events[topic].pop_back(); // unregister me 
	}
}

void ApplicationNotifierService::emit(std::string topic,std::string data) {
	if (!this->events[topic].empty()) {
		this->events[topic][0](data);		
	}
}