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
    char next_pos = 0;
    char start = 0;
    volatile Event tape[SIZE];

public:
    EventTape() {}
    void Add(Event item) {
        if (this->tape[this->next_pos].IsSome()) {
            this->start = this->next_pos + 1;
            if (this->start >= this->start)
                this->start = 0;
        }

        this->tape[this->next_pos++] = item;

        if (this->next_pos >= SIZE) {
            this->next_pos = 0;
        }
    }

    Event ReadFromStart(char pos) {
        char idx = this->start + pos;
        while (idx >= SIZE)
            idx -= SIZE;

        return this->tape[idx];
    }

    Event LastAdded() {
        char last = this->next_pos - 1;
        if (last == -1)
            last = SIZE - 1;
        return this->tape[last];
    }

    Event TakeFromStart() {
        char idx = this->start;
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
        this->start += 1;
        if (this->start >= SIZE)
            this->start = 0;
    }
};
