#include "../Domain/interrupt_registrar.h"
#include <Arduino.h>
#include "../Domain/logger.h"

InterruptRegistrar::InterruptRegistrar() {}
InterruptRegistrar::~InterruptRegistrar() {}




void InterruptRegistrar::attachDigitalInterrupt(byte digitalPin, void (*callback)(), byte mode) {	
	attachInterrupt(digitalPinToInterrupt(digitalPin), callback, mode);
}

// TODO: This doesn't really belong here
void InterruptRegistrar::inputPullup(byte dwPin) {
	pinMode(dwPin, INPUT_PULLUP);
}