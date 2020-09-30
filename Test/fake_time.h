#pragma once

class FakeTime {
private:
    unsigned long time = 0;

public:
    unsigned long CurrentTime();
    void IncrementTime(long ms);
};