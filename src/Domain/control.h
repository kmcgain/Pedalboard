#ifndef Control_H
#define Control_H


#include "function/function.h"
#include "button.h"
#include "screen.h"
#include "preset.h"
#include "tuner.h"

class Control {    
  private:
    Button* button;
    Function* function;
    Screen* screen;
    unsigned char buttonNumber;
    bool isDirty;
    char sequenceNumber;
    unsigned int lastStateHash;

  public:
    Control(Button* button, Function* function, Screen* screen, unsigned char buttonNumber);
    void HandleState();
    void PrintDebug();
    void RefreshScreen(Preset* currentPreset, TunerData& tuner);
    void Invalidate();

  private:
    void handlePress();
};
#endif