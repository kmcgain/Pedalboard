#ifndef LAYOUT_H
#define LAYOUT_H

#include "control.h"
#include "preset.h"
#include "tuner.h"

class Layout { 
  private:
    Control*** controls;
    byte rows, cols;
      
  public:
    Layout(Control*** controls, byte rows, byte cols);
    ~Layout();
    void init();
    void Exit();
    void ProcessOutstanding();
    void RefreshScreens(Preset* currentPreset, TunerData& tuner);
    void Invalidate();
    void PrintDebug();
};
#endif