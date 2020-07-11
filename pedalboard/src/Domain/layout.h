#ifndef LAYOUT_H
#define LAYOUT_H

#include "control.h"

class Layout { 
  private:
    Control*** controls;
    int rows, cols;
      
  public:
    Layout(Control*** controls, int rows, int cols);
    ~Layout();
    void init();
    void Exit();
    void ProcessOutstanding();
};
#endif