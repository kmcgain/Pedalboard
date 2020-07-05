
#include <Arduino.h>
#include "button.h"
#include "control.h"
#include "function.h"

Control::Control(Button* button, Function* function) {        
    this->button = button;
    this->function = function;
}

// Standard loop will call this so we can handle any button presses
void Control::HandleState() {
    // grab a button event and then exec function
}

void Control::handlePress() {

}