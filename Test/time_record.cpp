#include "pch.h"

#include "../Domain/time_record.h"
#include "fake_time_factory.h"


unsigned long time_millis() {
    return FakeTimeFactory::GetFakeTime()->CurrentTime();
}


