#pragma once

#include<iostream>
#include<map>
#include<vector>
#include<string>
#include "ThreadEvenHandler.h"
#include"..\CMUgraphicsLib\colors.h"
//#include "..\ApplicationFiguresHelperPanel\ApplicationFiguresHelperPanel.h"
// 
// 
// 
//this service working only with callbacks 
//so u can handle using ur own calls or u can handle this using Lambada Expression

class ApplicationFiguresHelperPanelManager;

class ApplicationManager;

enum PANEL_STATE { PANEL_OPEN, PANEL_CLOSE, PANAL_SENDING_COLOR, PANAL_SENDING_OVERLAP_STATE };

struct PanelListener {
	ApplicationFiguresHelperPanelManager* appPanelMngr;
	PANEL_STATE stat;
	int target;
	color selectedObjColor;
	int shapeOverLapState; // 0 or 1 
	bool threadClose;
};

class ThreadNotifier {

public:

	void on(std::string topic, ThreadEventsHandler*  handler);

	void off(std::string topic); //only one object will notify

	void emit(std::string topic,PanelListener* pl);


private:

	std::map<std::string, std::vector<ThreadEventsHandler*>>events;


};

