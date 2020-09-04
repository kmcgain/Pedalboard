#include "pch.h"
#include "button.h"
#include "control.h"
#include "function/function.h"
#include "logger.h"

Control::Control(Button* button, Function* function, Screen* screen) {        
    this->button = button;
    this->function = function;
    this->screen = screen;
}

// Standard loop will call this so we can handle any button presses
void Control::HandleState() {    
    // grab a button event and then exec function
    ButtonEvent btnEvent;
    do {
        btnEvent = this->button->TakeEvent();
        if (btnEvent.IsSome()) {
            switch (btnEvent.EventType) {
                case (ButtonEvent::button_event_type::Press):
                    Logger::log("Press\n");
                    this->function->Execute();
                    break;
                case (ButtonEvent::button_event_type::LongPress):
                    Logger::log("Long Press\n");
                    this->function->Execute();
                    break;
                case (ButtonEvent::button_event_type::Hold):
                    Logger::log("Hold\n");
                    this->function->Execute();
                    break;
                default:
                    Logger::log("Other\n");
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
    this->screen->DisplayFunction(this->function->Type());
}