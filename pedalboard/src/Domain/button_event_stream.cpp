#include "pch.h"

#include "time_record.h"
#include "button_event.h"
#include "button_event_stream.h"



void ButtonEventStream::RecordPress(unsigned long eventTime) {
    if (this->events.LastAdded().IsSome() && this->events.LastAdded().WasPress)
        return; // Don't need to record multiple presses in a row

    Event ev;
    ev.WasPress = true;
    ev.TimeMs = eventTime;
    
    this->events.Add(ev);
}

void ButtonEventStream::RecordRelease(unsigned long eventTime) {
    if (this->events.LastAdded().IsSome() && !this->events.LastAdded().WasPress)
        return; // Don't need to record multiple releases in a row

    Event ev;
    ev.WasPress = false;
    ev.TimeMs = eventTime;
    
    this->events.Add(ev); 
}

ButtonEvent ButtonEventStream::Take() {

    Event firstEvent = this->events.ReadFromStart(0);
    if (!firstEvent.IsSome())
        return ButtonEvent();
      
    if (!firstEvent.WasPress) {
        // Ignore and remove
        this->events.TakeFromStart();
        return ButtonEvent();
    }
    unsigned long currentTimeMs = time_millis();
    Event secondEvent = this->events.ReadFromStart(1);

    if (!secondEvent.IsSome()) {
        unsigned long timeDiffMs = currentTimeMs - firstEvent.TimeMs;
        if (timeDiffMs > ButtonEvent::LONG_HOLD_LIMIT_MS) {
            ButtonEvent result;
            result.EventType = ButtonEvent::button_event_type::Hold;
            result.HeldMs = timeDiffMs;
            result.EventTimeMs = firstEvent.TimeMs;
            return result;
        }
    }

    // Remove the events from tape as we have enough information to determine the event
    this->events.TakeFromStart();
    this->events.TakeFromStart();

    if (secondEvent.WasPress) {
        return ButtonEvent();
    }

    ButtonEvent result;
    unsigned long timeHeld = secondEvent.TimeMs - firstEvent.TimeMs;

    if (timeHeld < ButtonEvent::LONG_HOLD_START_MS) {
        result.EventType = ButtonEvent::button_event_type::Press;
        result.EventTimeMs = secondEvent.TimeMs;
    }
    else if (timeHeld <= ButtonEvent::LONG_HOLD_LIMIT_MS) {
        result.EventType = ButtonEvent::button_event_type::LongPress;
        result.EventTimeMs = secondEvent.TimeMs;
    }
    else {
        result.EventType = ButtonEvent::button_event_type::Hold;
        result.EventTimeMs = firstEvent.TimeMs;
        result.HeldMs = timeHeld;
    }

    return result;
}

