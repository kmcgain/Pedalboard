#ifndef LAYOUT_H
#define LAYOUT_H

#include <Arduino.h>
#include "control.h"

class Layout { 
  private:
    Control*** controls;
    int rows, cols;
      
  public:
    Layout(Control*** controls, int rows, int cols);
    void init();
    void Exit();
};
#endif