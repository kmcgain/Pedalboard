#include "pch.h"
#include "../Domain/pin.h"
#include "../Domain/constants.h"

bool pinStates[MAX_DIGITAL_PIN+1];

bool digitalPinHigh(int pinNumber) {
	return pinStates[pinNumber];
}

void setPinState(int pinNumber, bool state) {
	pinStates[pinNumber] = state;
}

int analogPinRead(int pinNumber) {
	return 4096;
}

