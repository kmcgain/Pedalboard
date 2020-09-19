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
        unsigned long pressTime;
        

    public:
        ButtonEventStream();
        void RecordPress(unsigned long eventTime);

        void RecordRelease(unsigned long eventTime);

        ButtonEvent Take();

        void PrintDebug();

    private:
        ButtonEvent takeAux();
        void recordPressAux(unsigned long eventTime);
        void recordReleaseAux(unsigned long eventTime);

};


#endif