#include "pch.h"
#include "button.h"
#include "control.h"
#include "function/function.h"
#include "logger.h"

Control::Control(Button* button, Function* function, Screen* screen, unsigned char buttonNumber) {
    this->button = button;
    this->function = function;
    this->screen = screen;
    this->buttonNumber = buttonNumber;
    this->isDirty = true;
}

// Standard loop will call this so we can handle any button presses
void Control::HandleState() {    
    // grab a button event and then exec function
    ButtonEvent btnEvent;
    do {
        btnEvent = this->button->TakeEvent();
        
        if (btnEvent.IsSome()) {
            this->isDirty = true;

            switch (btnEvent.EventType) {
                case (ButtonEvent::button_event_type::Press):
                    this->function->Execute();
                    break;
                case (ButtonEvent::button_event_type::LongPress):
                    this->function->Execute();
                    break;
                case (ButtonEvent::button_event_type::Hold):
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

void Control::PrintDebug() {
    this->button->PrintDebug();
}

void Control::RefreshScreen() {
    if (this->isDirty) {
        FunctionState* state = this->function->State();
        this->screen->DisplayFunction(state);
        this->isDirty = false;
    }
}