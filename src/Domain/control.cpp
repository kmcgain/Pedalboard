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
#ifdef DEBUG_LOG
                    char logMsg[50];
                    sprintf(logMsg, "Event: Press - %s - %d\n", this->function->Name(), this->buttonNumber);
                    Logger::log(logMsg);
#endif
                    this->function->Execute();
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

bool flushedAfterTuner = false;
void Control::RefreshScreen(Preset* currentPreset, TunerData& tuner) {    
    if (currentPreset != nullptr)
        this->function->UpdateState(currentPreset);
    FunctionState* state = this->function->State();
        
    auto newHashCode = state->HashCode();

    if ((this->buttonNumber == 7 && (tuner.Active || !flushedAfterTuner)) || this->isDirty || this->lastStateHash == -1 || newHashCode != this->lastStateHash) {                    
        flushedAfterTuner = this->buttonNumber == 7 && !tuner.Active; // this ensures we do a screen update after the tuner is switched off

        this->lastStateHash = newHashCode;
        this->screen->DisplayFunction(state, currentPreset, tuner);
        this->isDirty = false;
    }
}

void Control::Invalidate() {
    this->isDirty = true;
}