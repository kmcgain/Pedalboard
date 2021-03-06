#ifndef BUTTON_EVENT_H
#define BUTTON_EVENT_H

#include "some.h"

struct ButtonEvent : public Some {
    enum button_event_type {
        Press,
        Release,
        LongPress,
        Hold,
        None
    };

    static const unsigned short LONG_HOLD_LIMIT_MS = 1500;
    static const unsigned short LONG_HOLD_START_MS = 500;
    static const unsigned short PRESS_BUFFER_MS = 50;
    static const unsigned short RELEASE_TO_PRESS_BUFFER = 100;

    button_event_type EventType;

    /*
     * The time a button was held for, only relevant for Hold events
     */
    unsigned short HeldMs;

    /*
     * The event time for Press,LongPress is when the button is released.
     * For Hold it is when the button was first pressed
     */
    unsigned long EventTimeMs;

    ButtonEvent() {
        EventType = button_event_type::None;
        HeldMs = -1;
        EventTimeMs = -1;
    }

    bool IsSome() volatile {
        return EventType != ButtonEvent::button_event_type::None;
    }
};

#endif