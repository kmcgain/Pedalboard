#include "pch.h"

#include "time_record.h"
#include "button_event.h"
#include "button_event_stream.h"
#include "atomic_fn.h"
#include "logger.h"

static const int BUTTON_EVENT_BUFFER = 60;

void ButtonEventStream::RecordPress(unsigned long eventTime) {
    return AtomicFnVoid<ButtonEventStream>::Run(*this, &ButtonEventStream::recordPressAux, eventTime);
}

void ButtonEventStream::RecordRelease(unsigned long eventTime) {
    return AtomicFnVoid<ButtonEventStream>::Run(*this, &ButtonEventStream::recordReleaseAux, eventTime);
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
    int FoundAtIndex;
};

void cleanTape(int index, EventTape* tape) {
    for (int i = 0; i <= index; i++)
        tape->TakeFromStart();
}

ButtonEvent ButtonEventStream::takeAux() {
    const int MAX_DEBOUNCED = 10;
    DebouncedEvent events[MAX_DEBOUNCED];

    bool hasSome = true;
    int eventIndex = 0;
    int tapeIndex = 0;
    while (hasSome && eventIndex < MAX_DEBOUNCED) {
        auto event = this->events.ReadFromStart(tapeIndex);
        hasSome = event.IsSome();
        if (hasSome) {
            if (!events[eventIndex].IsSome()) {
                events[eventIndex].TimeMs = event.TimeMs;
                events[eventIndex].WasPress = event.WasPress;
                events[eventIndex].FoundAtIndex = tapeIndex;
            }
            else if (event.TimeMs < events[eventIndex].TimeMs + 20) {
                events[eventIndex].TimeMs = event.TimeMs;
                events[eventIndex].WasPress = event.WasPress;
                events[eventIndex].FoundAtIndex = tapeIndex;
            }
            else {
                // New Event!
                eventIndex++;
                events[eventIndex].TimeMs = event.TimeMs;
                events[eventIndex].WasPress = event.WasPress;
                events[eventIndex].FoundAtIndex = tapeIndex;
            }

            tapeIndex++;
        }
    }

    // Now we determine if we have useful debounced events, we may need to wait if we are still in hold position
    // It is also possible that a button press is a bit wonky and in 1 debounced event it is just a single release.
     
    if (!events[0].IsSome())
        return ButtonEvent();

    // Sequence options:
    // Release -> Event
    //
    // Release + Release 
    // Press + Press 
    // Press + Release

    // Approach, we must end on Release for it to be a press, we may never detect a full press event
    // This means we can ignore Presses in a row

    ButtonEvent result;
    if (!events[0].WasPress) {
        // This is a case where we couldn't identify a proper press/release sequence. Just suppress it otherwise we get false positives
        cleanTape(events[0].FoundAtIndex, &this->events);

        return ButtonEvent();
    }

    eventIndex = 0;
    while (events[eventIndex].IsSome() && events[eventIndex].WasPress)
        eventIndex++;

    // Now eventIndex-1 is the Press, and eventIndex is either nothing or release

    if (!events[eventIndex].IsSome()) {
        // We still only have a hanging press so leave it on tape
        return ButtonEvent();
    }

    // We got a press release cycle between events 0 and eventIndex
    cleanTape(events[eventIndex].FoundAtIndex, &this->events);

    // We've got our 2 events to determine our outcome    
    unsigned long timeHeld = events[eventIndex].TimeMs - events[0].TimeMs;

    if (timeHeld < ButtonEvent::LONG_HOLD_START_MS) {
        result.EventType = ButtonEvent::button_event_type::Press;
        result.EventTimeMs = events[eventIndex].TimeMs;
    }
    else if (timeHeld <= ButtonEvent::LONG_HOLD_LIMIT_MS) {
        result.EventType = ButtonEvent::button_event_type::LongPress;
        result.EventTimeMs = events[eventIndex].TimeMs;
    }
    else {
        result.EventType = ButtonEvent::button_event_type::Hold;
        result.EventTimeMs = events[0].TimeMs;
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