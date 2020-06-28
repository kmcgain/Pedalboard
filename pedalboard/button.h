#ifndef BUTTON_H
#define BUTTON_H

#include "common/maybe.h"
#include "button_event.h"

class Button {
    public:
        Button();
        void OnPress();
        void OnRelease();
        Maybe<ButtonEvent> TakeEvent();
};

#endif