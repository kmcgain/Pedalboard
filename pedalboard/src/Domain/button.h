#ifndef BUTTON_H
#define BUTTON_H

#include "maybe.h"
#include "button_event.h"
#include "button_event_stream.h"

class Button {
    private:
        ButtonEventStream buttonEventStream;

    public:
        Button();
        void OnPress();
        void OnRelease();
        ButtonEvent TakeEvent();
};

#endif