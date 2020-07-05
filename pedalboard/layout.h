#ifndef LAYOUT_H
#define LAYOUT_H

#include <Arduino.h>
#include "control.h"

class Layout { 
  private:
    Control** controls;
    size_t rows, cols;
      
  public:
    Layout(Control** controls, size_t rows, size_t cols);
    void init();
};
#endif