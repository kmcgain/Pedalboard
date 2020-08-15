#pragma once

#include "some.h"

class Event : public Some {
public:
    Event() {}
    Event(const Event& toCopy) {
        WasPress = toCopy.WasPress;
        TimeMs = toCopy.TimeMs;
    }

    bool IsSome() { return false; }

    bool WasPress;
    unsigned long TimeMs;
};
