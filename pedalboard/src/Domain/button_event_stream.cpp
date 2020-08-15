#include "pch.h"

#include "time_record.h"
#include "button_event.h"
#include "button_event_stream.h"
#include "atomic_fn.h"
#include "logger.h"

static const int BUTTON_EVENT_BUFFER = 60;

void ButtonEventStream::RecordPress(unsigned long eventTime) {
    //Logger::log("Press\n");
    return AtomicFnVoid<ButtonEventStream>::Run(*this, &ButtonEventStream::recordPressAux, eventTime);
}

void ButtonEventStream::RecordRelease(unsigned long eventTime) {
    //Logger::log("Release\n");
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

ButtonEvent ButtonEventStream::takeAux() {
    auto event = this->events.ReadFromStart(0);
    if (!event.IsSome())
        return ButtonEvent();

    Event events[2]; // we process 2 events at a time

    unsigned int startTime = event.TimeMs;
    bool wasPress = event.WasPress;

    unsigned int lastTime = startTime;
    bool hasMore = true;
    int firstIndex = 1;
    while (hasMore) {
        event = this->events.ReadFromStart(firstIndex++);
        hasMore = event.IsSome() && event.TimeMs < startTime + BUTTON_EVENT_BUFFER;
        
        if (hasMore) {
            lastTime = event.TimeMs;
            wasPress = event.WasPress;
        }
    }
    firstIndex--;

    events[0].TimeMs = startTime;
    events[0].WasPress = wasPress;

    if (!wasPress) {
        Logger::log("\nNotPress\n");
        for (int i = 0; i < firstIndex; i++)
           this->events.TakeFromStart();
        return ButtonEvent();
    }

    int secondIndex = firstIndex;
    event = this->events.ReadFromStart(secondIndex++);
    hasMore = event.IsSome();
    startTime = event.TimeMs;
    wasPress = event.WasPress;

    while (hasMore) {
        event = this->events.ReadFromStart(secondIndex++);
        hasMore = event.IsSome() && event.TimeMs < startTime + BUTTON_EVENT_BUFFER;

        if (hasMore) {
            lastTime = event.TimeMs;
            wasPress = event.WasPress;
        }
    }

    secondIndex--;
    
    events[1].TimeMs = startTime;
    events[1].WasPress = wasPress;
    
    Logger::log("Got events\n1: ");
    Logger::log(events[0].TimeMs);
    Logger::log(" - ");
    Logger::log(events[0].WasPress);
    Logger::log("\n");

    Logger::log("\n2: ");
    Logger::log(events[1].TimeMs);
    Logger::log(" - ");
    Logger::log(events[1].WasPress);
    Logger::log("\n");
    
    if (events[0].WasPress == events[1].WasPress) {
        Logger::log("Removing first event due to duplicate\n");
        // WE are just going to remove first event as it's a duplicate
        for (int i = 0; i < firstIndex; i++)
            this->events.TakeFromStart();

        // THis is not-ideal. We  could continue processing rather than coming around for another loop
        return ButtonEvent();
    }

    if (events[1].WasPress) {
        //Didn't finish with a press
        return ButtonEvent();
    }

    // At this stage we can clean the tape
    for (int i = 0; i < secondIndex; i++)
        this->events.TakeFromStart();
    
    // We've got our 2 events to determine our outcome
    ButtonEvent result;
    unsigned long timeHeld = events[1].TimeMs - events[0].TimeMs;
    
    if (timeHeld < ButtonEvent::LONG_HOLD_START_MS) {
        result.EventType = ButtonEvent::button_event_type::Press;
        result.EventTimeMs = events[1].TimeMs;
    }
    else if (timeHeld <= ButtonEvent::LONG_HOLD_LIMIT_MS) {
        result.EventType = ButtonEvent::button_event_type::LongPress;
        result.EventTimeMs = events[1].TimeMs;
    }
    else {
        result.EventType = ButtonEvent::button_event_type::Hold;
        result.EventTimeMs = events[0].TimeMs;
        result.HeldMs = timeHeld;
    }

    Logger::log("We got an actual event!!\n");
    
    return result;
}

ButtonEvent ButtonEventStream::Take() {
    return AtomicFn<ButtonEvent, ButtonEventStream>::Run(*this, &ButtonEventStream::takeAux);
}

void ButtonEventStream::PrintDebug() {
    this->events.PrintDebug();
}