#include "pch.h"

#include "time_record.h"
#include "button_event.h"
#include "button_event_stream.h"
#include "atomic_fn.h"
#include "logger.h"

#define MAX_DEBOUNCED 50

ButtonEventStream::ButtonEventStream() {
    this->pressTime = -1;
    this->lastReleaseTime = -1;
}

void ButtonEventStream::RecordPress(unsigned long eventTime) {
    AtomicFnVoid<ButtonEventStream>::Run(*this, &ButtonEventStream::recordPressAux, eventTime);
}

void ButtonEventStream::RecordRelease(unsigned long eventTime) {
    AtomicFnVoid<ButtonEventStream>::Run(*this, &ButtonEventStream::recordReleaseAux, eventTime);
}

void ButtonEventStream::recordPressAux(unsigned long eventTime) {
    if (this->events.LastAdded().IsSome() && this->events.LastAdded().WasPress)
        return; // Don't need to record multiple presses in a row

    Event ev;
    ev.WasPress = true;
    ev.TimeMs = eventTime;    
    
    this->events.Add(ev);
}

void ButtonEventStream::recordReleaseAux(unsigned long eventTime) {
    if (this->events.LastAdded().IsSome() && !this->events.LastAdded().WasPress)
        return; // Don't need to record multiple releases in a row

    Event ev;
    ev.WasPress = false;
    ev.TimeMs = eventTime;
    
    this->events.Add(ev); 
}

struct DebouncedEvent {
    DebouncedEvent() {
        TimeMs = -1;
        WasPress = false;
        FoundAtIndex = -1;
    }

    bool IsSome() volatile {
        return TimeMs != -1;
    }

    bool WasPress;
    unsigned long TimeMs;
    char FoundAtIndex;
};

void cleanTape(char index, EventTape* tape) {
    for (char i = 0; i <= index; i++)
        tape->TakeFromStart();
}



ButtonEvent ButtonEventStream::takeAux() {
    DebouncedEvent debouncedEvent;

    bool hasSome = true;
    char tapeIndex = 0;
    while (hasSome && tapeIndex < MAX_DEBOUNCED) {
        auto event = this->events.ReadFromStart(tapeIndex);
        hasSome = event.IsSome();
        if (hasSome) {
            if (!debouncedEvent.IsSome()) {
                debouncedEvent.TimeMs = event.TimeMs;
                debouncedEvent.WasPress = event.WasPress;
                debouncedEvent.FoundAtIndex = tapeIndex;
            }
            else if (event.TimeMs < debouncedEvent.TimeMs + 20) {
                debouncedEvent.TimeMs = event.TimeMs;
                debouncedEvent.WasPress = event.WasPress;
                debouncedEvent.FoundAtIndex = tapeIndex;
            }
            else {
                // New Event! - we only need 1
                break;
            }

            tapeIndex++;
        }
    }

    // Now we determine if we have useful debounced events, we may need to wait if we are still in hold position
    // It is also possible that a button press is a bit wonky and in 1 debounced event it is just a single release.

    if (!debouncedEvent.IsSome())
        return ButtonEvent();

    // All other cases we'll clean the event from the tape.
    cleanTape(debouncedEvent.FoundAtIndex, &this->events);

    ButtonEvent result;
    if (debouncedEvent.WasPress) {
        if (this->pressTime == -1) {
            if (this->lastReleaseTime != -1 && debouncedEvent.TimeMs - this->lastReleaseTime < ButtonEvent::RELEASE_TO_PRESS_BUFFER) {
                // bad press detected, suppress
                return result;
            }

            this->pressTime = debouncedEvent.TimeMs;
            

            result.EventType = ButtonEvent::button_event_type::Press;
            result.EventTimeMs = debouncedEvent.TimeMs;
        }
        //else {
            // we've already given a press event so we suppress
            // We could actually continue processing more events if we wanted to but to keep things simple we'll only deal with 1 event per cycle
        //}
        return result;
    }

    if (this->pressTime == -1) {
        // we got a release but never recorded the press. Ignore
        return result;
    }

    // Release
    unsigned short timeHeld = debouncedEvent.TimeMs - this->pressTime;    

    if (timeHeld < ButtonEvent::PRESS_BUFFER_MS) {
        // suppress, happened too quickly so we are seeing up,down,up for one action
        return result;
    }

    this->lastReleaseTime = debouncedEvent.TimeMs;
    this->pressTime = -1;
    
    if (timeHeld < ButtonEvent::LONG_HOLD_START_MS) {
        result.EventType = ButtonEvent::button_event_type::Release;
        result.EventTimeMs = debouncedEvent.TimeMs;
    }
    else if (timeHeld <= ButtonEvent::LONG_HOLD_LIMIT_MS) {
        result.EventType = ButtonEvent::button_event_type::LongPress;
        result.EventTimeMs = debouncedEvent.TimeMs;
    }
    else {
        // TODO: Currently we can't react to hold mid hold.. only when the hold ends. Will fix when I find a use case
        result.EventType = ButtonEvent::button_event_type::Hold;
        result.EventTimeMs = debouncedEvent.TimeMs;
        result.HeldMs = timeHeld;
    }
    return result;
}

ButtonEvent ButtonEventStream::Take() {
    return AtomicFn<ButtonEvent, ButtonEventStream>::Run(*this, &ButtonEventStream::takeAux);
}

void ButtonEventStream::PrintDebug() {
    this->events.PrintDebug();
}