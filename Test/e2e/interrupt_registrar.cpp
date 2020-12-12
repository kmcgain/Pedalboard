#include "pch.h"
#include "../../src/Domain/interrupt_registrar.h"

InterruptRegistrar::InterruptRegistrar() {
}
InterruptRegistrar::~InterruptRegistrar() {}

void InterruptRegistrar::attachDigitalInterrupt(byte digitalPin, void (*callback)(), byte mode) {}

void InterruptRegistrar::inputPullup(byte digitalPin) {}
