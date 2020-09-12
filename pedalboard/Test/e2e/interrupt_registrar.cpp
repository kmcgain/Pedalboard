#include "pch.h"
#include "../../src/Domain/interrupt_registrar.h"

InterruptRegistrar::InterruptRegistrar() {
}
InterruptRegistrar::~InterruptRegistrar() {}

void InterruptRegistrar::attachDigitalInterrupt(char digitalPin, void (*callback)(), unsigned char mode) {}

void InterruptRegistrar::inputPullup(char digitalPin) {}
