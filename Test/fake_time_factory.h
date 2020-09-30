#pragma once

#include "fake_time.h"

class FakeTimeFactory {
    private:
        static FakeTime fakeTime;
        
    public:
        static FakeTime* GetFakeTime();
};
