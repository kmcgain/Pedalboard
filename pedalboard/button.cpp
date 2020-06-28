
#include <Arduino.h>
#include "common/tape.h"
#include "button_event.h"


class Button {
    
    private:
        /*
        * This concept exists so interrupts can record multiple events before the main
        * loop gets around to processing them. 
        */
        class ButtonEventStream {
            
            private:
                class Event {
                    public:
                        bool WasPress;
                        unsigned long TimeMs;                    
                };
                
                Tape<Event> events;
                

            public:
                void RecordPress(unsigned long eventTime) {
                    if (this->events.LastAdded().IsSome() && this->events.LastAdded().Value().WasPress)
                        return; // Don't need to record multiple presses in a row

                    Event ev;
                    ev.WasPress = true;
                    ev.TimeMs = eventTime;
                    this->events.Add(ev);
                }

                void RecordRelease(unsigned long eventTime) {
                    if (this->events.LastAdded().IsSome() && !this->events.LastAdded().Value().WasPress)
                        return; // Don't need to record multiple releases in a row

                    Event ev;
                    ev.WasPress = false;
                    ev.TimeMs = eventTime;
                    this->events.Add(ev);
                }

                Maybe<ButtonEvent> Take() {
                    Maybe<Event> firstEvent = this->events.ReadFromStart(0);
                    if (firstEvent.IsNone())
                        return Maybe<ButtonEvent>::None();

                    Event firstEventValue = firstEvent.Value();

                    if (!firstEventValue.WasPress) {
                        // Ignore and remove
                        this->events.TakeFromStart(0);
                        return;
                    }
                    unsigned long currentTimeMs = millis();

                    Maybe<Event> secondEvent = this->events.ReadFromStart(1);

                    if (secondEvent.IsNone()) {
                        unsigned long timeDiffMs = currentTimeMs - firstEventValue.TimeMs;
                        if (timeDiffMs > ButtonEvent::LONG_HOLD_LIMIT_MS) {
                            ButtonEvent result;
                            result.EventType = ButtonEvent::button_event_type::Hold;
                            result.HeldMs = timeDiffMs;
                            result.EventTimeMs = firstEventValue.TimeMs;
                            return Maybe<ButtonEvent>::Some(result);
                        }
                    }

                    // Remove the events from tape as we have enough information to determine the event
                    this->events.TakeFromStart(0);
                    this->events.TakeFromStart(0);

                    Event secondEventValue = secondEvent.Value();

                    if (secondEventValue.WasPress) {
                        return Maybe<ButtonEvent>::None();
                    }

                    ButtonEvent result;
                    unsigned long timeHeld = secondEventValue.TimeMs - secondEventValue.TimeMs;
                    
                    if (timeHeld < ButtonEvent::LONG_HOLD_START_MS) {
                        result.EventType = ButtonEvent::button_event_type::Press;
                        result.EventTimeMs = secondEventValue.TimeMs;
                    }
                    else if (timeHeld <= ButtonEvent::LONG_HOLD_LIMIT_MS) {
                        result.EventType = ButtonEvent::button_event_type::LongPress;
                        result.EventTimeMs = secondEventValue.TimeMs;
                    }
                    else {
                        result.EventType = ButtonEvent::button_event_type::Hold;
                        result.EventTimeMs = firstEventValue.TimeMs;
                        result.HeldMs = timeHeld;
                    }

                    return Maybe<ButtonEvent>::Some(result);
                }

        };
        
        ButtonEventStream buttonEventStream;

    public:        
        Button() {}

        // interrupt
        OnPress() {
            this->buttonEventStream.RecordPress(millis());
        }

        // interrupt
        OnRelease() {
            this->buttonEventStream.RecordRelease(millis());
        }

        ButtonEvent TakeEvent() {
            this->buttonEventStream.Take();
        }


};