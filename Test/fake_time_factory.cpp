#include "pch.h"
#include "fake_time_factory.h"

FakeTime* FakeTimeFactory::GetFakeTime() {
    return &FakeTimeFactory::fakeTime;
};

FakeTime FakeTimeFactory::fakeTime;