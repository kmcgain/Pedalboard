
#include <Arduino.h>
#include "button.h"

class Control {  
  

  private:
    Button button;

  public:
    Control(Button button) {        
        this->button = button;
    }

    // Standard loop will call this so we can handle any button presses
    void HandleState() {
        
    }

  private:
    void handlePress() {

    }
};