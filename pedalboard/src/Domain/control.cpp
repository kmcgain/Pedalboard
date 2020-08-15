#include "pch.h"
#include "button.h"
#include "control.h"
#include "function/function.h"
#include "logger.h"

Control::Control(Button* button, Function* function) {        
    this->button = button;
    this->function = function;
}

// Standard loop will call this so we can handle any button presses
void Control::HandleState() {    
    // grab a button event and then exec function
    ButtonEvent btnEvent;
    do {
        btnEvent = this->button->TakeEvent();
        if (btnEvent.IsSome()) {
            Logger::log("Found event!\n");

            auto name = this->function->Name();
            Logger::log(name);
            switch (btnEvent.EventType) {
                case (ButtonEvent::button_event_type::Press):
                    Logger::log("Press\n");
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