#pragma once

enum MOUSE_STATES { STATE_UP=1, STATE_MOVE=2 , STATE_DOWN=3, STATE_SIZING, STATE_PAINTING}; //LIKE A CONSTANT

struct MouseStPoint {
    int x;
    int y;
    MOUSE_STATES state;
    bool mouseDown;
    int delKey=0;
    int ctrlKey = 0;
    std::string msg;
};