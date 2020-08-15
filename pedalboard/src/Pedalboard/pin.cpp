#include "../Domain/pin.h"
#include <Arduino.h>

bool digitalPinHigh(int pin) {
	return digitalRead(2) == HIGH;
}