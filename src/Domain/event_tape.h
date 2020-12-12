#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstdio>
#endif

#include "button_event_stream_event.h"
#include "logger.h"

#define SIZE 60

class EventTape {
private:
    volatile byte next_pos = 0;
    volatile byte start = 0;
    volatile Event tape[SIZE];

public:
    EventTape() {}
    void Add(Event item) {
        byte nextIndex = this->next_pos;
        if (nextIndex >= SIZE) {
            nextIndex = 0;
        }

        if (this->tape[nextIndex].IsSome()) {
            this->start = nextIndex + 1 >= SIZE ? 0 : nextIndex + 1;            
        }

        this->tape[nextIndex] = item;

        nextIndex = this->next_pos + 1;
        this->next_pos = nextIndex >= SIZE ? 0 : nextIndex;
    }

    Event ReadFromStart(byte pos) {
        if (pos < 0)
            return Event();

        byte idx = this->start + pos;
        while (idx >= SIZE)
            idx -= SIZE;

        return this->tape[idx];
    }

    Event LastAdded() {
        byte last = this->next_pos - 1;
        if (last <= -1)
            last = SIZE - 1;
        return this->tape[last];
    }

    Event TakeFromStart() {
        byte idx = this->start;
        while (idx >= SIZE)
            idx -= SIZE;

        Event item = this->tape[idx];
        this->tape[idx] = Event();
        this->incrStart();

        return item;
    }

    void PrintDebug() {
        char logData[100];

        sprintf(logData, "Tape: \nStart: %d\nNext: %d\n", this->start, this->next_pos);

        Logger::log(logData);

        for (int i = 0; i < SIZE; i++) {
            sprintf(logData, "%d: %d - %d - %d\n", i, (int)this->tape[i].IsSome(), (int)this->tape[i].WasPress, (int)this->tape[i].TimeMs);
            Logger::log(logData);            
        }        
    }

private:
    void incrStart() {
        byte nextStart = this->start + 1;
        this->start = (nextStart >= SIZE) 
            ? 0
            : nextStart;        
    }
};
