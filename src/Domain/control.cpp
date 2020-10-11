#include "pch.h"
#include "button.h"
#include "control.h"
#include "function/function.h"
#include "logger.h"

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstdio>
#endif

Control::Control(Button* button, Function* function, Screen* screen, unsigned char buttonNumber) {
    this->button = button;
    this->function = function;
    this->screen = screen;
    this->buttonNumber = buttonNumber;
    this->isDirty = true;
    this->lastStateHash = -1;
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
                    this->function->Execute();
                    Logger::log("Event: Press\n");
                    break;
                case (ButtonEvent::button_event_type::Release):
                    break;
                case (ButtonEvent::button_event_type::LongPress):
                    //this->function->Execute();
                    break;
                case (ButtonEvent::button_event_type::Hold):
                    //this->function->Execute();
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
//char logMsg[50];
void Control::RefreshScreen(Preset* currentPreset) {    
    if (currentPreset != nullptr)
        this->function->UpdateState(currentPreset);
    FunctionState* state = this->function->State();
        
    auto newHashCode = state->HashCode();
    if (this->isDirty || this->lastStateHash == -1 || newHashCode != this->lastStateHash) {            
        this->lastStateHash = newHashCode;
        this->screen->DisplayFunction(state, currentPreset);
        this->isDirty = false;
    }
}

void Control::Invalidate() {
    this->isDirty = true;
}