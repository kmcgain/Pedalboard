#include "../Domain/interrupt_registrar.h"
#include <Arduino.h>

InterruptRegistrar::InterruptRegistrar() {}
InterruptRegistrar::~InterruptRegistrar() {}

void InterruptRegistrar::attachDigitalInterrupt(int digitalPin, void (*callback)(), unsigned int mode) {
	attachInterrupt(digitalPinToInterrupt(digitalPin), callback, mode);
}