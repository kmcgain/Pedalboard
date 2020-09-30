#pragma once

#include "some.h"

class Event : public Some {
public:
    Event() {
        TimeMs = -1;
        WasPress = false;
    }
    Event(const Event& toCopy) {
        WasPress = toCopy.WasPress;
        TimeMs = toCopy.TimeMs;
    }

    Event(const volatile Event& o) {
        WasPress = o.WasPress;
        TimeMs = o.TimeMs;
    }

    Event& operator=(const Event& ev) {
        WasPress = ev.WasPress;
        TimeMs = ev.TimeMs;
        return *this;
    }

    volatile Event& operator=(const Event& ev) volatile {
        WasPress = ev.WasPress;
        TimeMs = ev.TimeMs;
        return *this;
    }

    Event& operator=(const volatile Event& ev) {
        WasPress = ev.WasPress;
        TimeMs = ev.TimeMs;
        return *this;
    }
       
    volatile Event& operator=(const volatile Event& ev) volatile {
        WasPress = ev.WasPress;
        TimeMs = ev.TimeMs;
        return *this;
    }

    bool IsSome() volatile { 
        return TimeMs != -1;
    }
    
    bool WasPress;
    unsigned long TimeMs;

};
