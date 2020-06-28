#ifndef BUTTON_EVENT_H
#define BUTTON_EVENT_H

struct ButtonEvent {
    enum button_event_type {
        Press,
        LongPress,
        Hold
    };

    static const unsigned int LONG_HOLD_LIMIT_MS = 1500;
    static const unsigned int LONG_HOLD_START_MS = 500;

    button_event_type EventType;

    /*
     * The time a button was held for, only relevant for Hold events
     */
    unsigned long HeldMs;

    /*
     * The event time for Press,LongPress is when the button is released.
     * For Hold it is when the button was first pressed
     */
    unsigned long EventTimeMs;
};

#endif