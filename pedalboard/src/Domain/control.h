#ifndef Control_H
#define Control_H


#include "function/function.h"
#include "button.h"

class Control {    
  private:
    Button* button;
    Function* function;

  public:
    Control(Button* button, Function* function);
    void HandleState();

  private:
    void handlePress();
};
#endif