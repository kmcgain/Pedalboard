#include "../Domain/interrupt_registrar.h"
#include <Arduino.h>
#include "../Domain/logger.h"

InterruptRegistrar::InterruptRegistrar() {}
InterruptRegistrar::~InterruptRegistrar() {}




void InterruptRegistrar::attachDigitalInterrupt(int digitalPin, void (*callback)(), unsigned int mode) {		
	attachInterrupt(digitalPinToInterrupt(digitalPin), callback, mode);
}

// TODO: This doesn't really belong here
void InterruptRegistrar::inputPullup(int dwPin) {
	pinMode(dwPin, INPUT_PULLUP);
}