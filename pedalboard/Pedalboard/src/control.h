#ifndef Control_H
#define Control_H

#include "button.h"
#include "function.h"

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