#pragma once

#include<iostream>
#include<map>
#include<vector>
#include<string>
//this service working only with callbacks 
//so u can handle using ur own calls or u can handle this using Lambada Expression
class ApplicationNotifierService {

public:

	void on(std::string topic, void(*handler)(std::string));

	void off(std::string topic); //only one object will notify

	void emit(std::string topic,std::string data);


private:

	std::map<std::string, std::vector<void(*)(std::string data)>>events;


};