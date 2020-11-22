
#include "pch.h"
#include "fake_interrupt_registrar.h"

FakeInterruptRegistrar::FakeInterruptRegistrar(BoardConstants &bc) {
    this->bc = bc;
}
FakeInterruptRegistrar::~FakeInterruptRegistrar() {}


void FakeInterruptRegistrar::attachDigitalInterrupt(char digitalPin, void (*callback)(), unsigned char mode) {  
    if (mode != bc.Change)
        throw std::runtime_error("Bad interrupt attachment");

    this->changingCallbacks[digitalPin] = callback;
}

void FakeInterruptRegistrar::fireInterrupt(char digitalPin, char mode) {
    if (mode != bc.Change)
        throw std::runtime_error("Bad interrupt fire");

    this->changingCallbacks[digitalPin]();    
}

void FakeInterruptRegistrar::inputPullup(char dwPin) {
    // no op
}