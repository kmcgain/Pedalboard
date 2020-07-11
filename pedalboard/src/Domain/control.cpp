#include "pch.h"
#include "button.h"
#include "control.h"
#include "function/function.h"

Control::Control(Button* button, Function* function) {        
    this->button = button;
    this->function = function;
}

// Standard loop will call this so we can handle any button presses
void Control::HandleState() {
    // grab a button event and then exec function
    Maybe<ButtonEvent> btnEvent;
    do {
        btnEvent = this->button->TakeEvent();
        if (btnEvent.IsSome()) {
            switch (btnEvent.Value().EventType) {
                case (ButtonEvent::button_event_type::Press):
                    this->function->Execute();
                    break;
                default:
                    break;
            }
        }
    } while (btnEvent.IsSome());
}

void Control::handlePress() {

}