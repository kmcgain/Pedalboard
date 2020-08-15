#ifndef BUTTON_EVENT_STREAM_H
#define BUTTON_EVENT_STREAM_H

#include "time_record.h"
#include "tape.h"
#include "button_event.h"
#include "some.h"
#include "event_tape.h"

/*
* This concept exists so interrupts can record multiple events before the main
* loop gets around to processing them. 
*/
class ButtonEventStream {
    
    private:
        
        EventTape events;
        

    public:
        void RecordPress(unsigned long eventTime);

        void RecordRelease(unsigned long eventTime);

        ButtonEvent Take();
};


#endif