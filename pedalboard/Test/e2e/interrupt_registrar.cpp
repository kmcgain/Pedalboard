#include "pch.h"
#include "../../src/Domain/interrupt_registrar.h"

InterruptRegistrar::InterruptRegistrar() {
}
InterruptRegistrar::~InterruptRegistrar() {}

void InterruptRegistrar::attachDigitalInterrupt(int digitalPin, void (*callback)(), unsigned int mode) {}
