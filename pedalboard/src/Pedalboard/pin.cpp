#include "../Domain/pin.h"
#include <Arduino.h>

bool digitalPinHigh(int pin) {
	return digitalRead(pin) == HIGH;
}

int analogPinRead(int pin) {
	return analogRead(pin);
}