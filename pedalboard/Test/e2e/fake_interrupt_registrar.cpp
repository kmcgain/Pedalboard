
#include "pch.h"
#include "fake_interrupt_registrar.h"

FakeInterruptRegistrar::FakeInterruptRegistrar(BoardConstants &bc) {
    this->bc = bc;
}
FakeInterruptRegistrar::~FakeInterruptRegistrar() {}


void FakeInterruptRegistrar::attachDigitalInterrupt(int digitalPin, void (*callback)(), unsigned int mode) {
    if (mode == 1)
        this->fallingCallbacks[digitalPin] = callback;
    if (mode == 2)
        this->risingCallbacks[digitalPin] = callback;
}

void FakeInterruptRegistrar::fireInterrupt(int digitalPin, int mode) {
    if (mode == 1)
        this->fallingCallbacks[digitalPin]();
    if (mode == 2)
        this->risingCallbacks[digitalPin]();
}

void FakeInterruptRegistrar::inputPullup(int dwPin) {
    // no op
}