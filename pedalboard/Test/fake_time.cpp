#include "pch.h"
#include "fake_time.h"

unsigned long FakeTime::CurrentTime() {
    return this->time;
}

void FakeTime::IncrementTime(long ms) {
    this->time += ms;
}
