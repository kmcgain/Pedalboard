#ifndef Control_H
#define Control_H


#include "function/function.h"
#include "button.h"
#include "screen.h"

class Control {    
  private:
    Button* button;
    Function* function;
    Screen* screen;

  public:
    Control(Button* button, Function* function, Screen* screen);
    void HandleState();
    void PrintDebug();
    void RefreshScreen();

  private:
    void handlePress();
};
#endif