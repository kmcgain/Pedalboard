#pragma once
#include "button_event_stream_event.h"
#include "logger.h"

class EventTape {
private:
    static const int SIZE = 100;
    int next_pos = 0;
    int start = 0;
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

    Event ReadFromStart(int pos) {
        int idx = this->start + pos;
        while (idx >= SIZE)
            idx -= SIZE;

        return this->tape[idx];
    }

    Event LastAdded() {
        int last = this->next_pos - 1;
        if (last == -1)
            last = SIZE - 1;
        return this->tape[last];
    }

    Event TakeFromStart() {
        int idx = this->start;
        while (idx >= SIZE)
            idx -= SIZE;

        Event item = this->tape[idx];
        this->tape[idx] = Event();
        this->incrStart();

        return item;
    }

    void PrintDebug() {
        Logger::log("Tape: \nStart: ");
        Logger::log(this->start);
        Logger::log("\nNext: ");
        Logger::log(this->next_pos);
        Logger::log("\n");

        for (int i = 0; i < SIZE; i++) {
            Logger::log(i);
            Logger::log(": ");
            Logger::log((int)this->tape[i].IsSome());
            Logger::log(" -  ");
            Logger::log((int)this->tape[i].WasPress);
            Logger::log(" -  ");
            Logger::log((int)this->tape[i].TimeMs);
            Logger::log("\n");
        }        
    }

private:
    void incrStart() {
        this->start += 1;
        if (this->start >= SIZE)
            this->start = 0;
    }
};
