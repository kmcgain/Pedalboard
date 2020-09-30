#ifndef LAYOUT_H
#define LAYOUT_H

#include "control.h"
#include "preset.h"

class Layout { 
  private:
    Control*** controls;
    char rows, cols;
      
  public:
    Layout(Control*** controls, char rows, char cols);
    ~Layout();
    void init();
    void Exit();
    void ProcessOutstanding();
    void RefreshScreens(Preset* currentPreset);
    void Invalidate();
    void PrintDebug();
};
#endif