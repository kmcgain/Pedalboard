#ifndef Control_H
#define Control_H

#include "button.h"

class Control {    
  private:
    Button* button;

  public:
    Control(Button* button);
    void HandleState();

  private:
    void handlePress();
};
#endif