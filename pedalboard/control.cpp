
#include <Arduino.h>
#include "button.h"
#include "control.h"

Control::Control(Button* button) {        
    this->button = button;
}

// Standard loop will call this so we can handle any button presses
void Control::HandleState() {
    
}

void Control::handlePress() {

}