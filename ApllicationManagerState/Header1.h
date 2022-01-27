#pragma once

//class CFigure; //forward class declaration
class ApplicationManagerState {
public:
    int MouseXPOS;
    int MouseYPOS;
    int MouseOnDown; // 0 or 1 
    int MouseOnMove; // 0 or 1 
    int MouseOnRelease; // 0 or 1 
    void* selectedShape;
};