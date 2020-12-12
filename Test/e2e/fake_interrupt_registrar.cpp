
#include "pch.h"
#include "fake_interrupt_registrar.h"

FakeInterruptRegistrar::FakeInterruptRegistrar(BoardConstants &bc) {
    this->bc = bc;
}
FakeInterruptRegistrar::~FakeInterruptRegistrar() {}


void FakeInterruptRegistrar::attachDigitalInterrupt(byte digitalPin, void (*callback)(), byte mode) {  
    if (mode != bc.Change)
        throw std::runtime_error("Bad interrupt attachment");

    this->changingCallbacks[digitalPin] = callback;
}

void FakeInterruptRegistrar::fireInterrupt(byte digitalPin, byte mode) {
    if (mode != bc.Change)
        throw std::runtime_error("Bad interrupt fire");

    this->changingCallbacks[digitalPin]();    
}

void FakeInterruptRegistrar::inputPullup(byte dwPin) {
    // no op
}