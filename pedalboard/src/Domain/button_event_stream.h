#ifndef BUTTON_EVENT_STREAM_H
#define BUTTON_EVENT_STREAM_H

#include "time_record.h"
#include "tape.h"
#include "button_event.h"

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
        
        Tape<Event, 1000> events;
        

    public:
        void RecordPress(unsigned long eventTime);

        void RecordRelease(unsigned long eventTime);

        Maybe<ButtonEvent> Take();
};


#endif