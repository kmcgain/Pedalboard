#pragma once

#include "axe_controller.h"
#include "pin.h"

#define analogPin0 54
#define analogPin1 55

#define change_threshold 2

class Expression {
private: 
	AxeController* axeController;
	short pin;
	short oldValue = -1;
	short expNumber;

public:
	Expression(short expNumber, AxeController* axeController) {					
		this->axeController = axeController;
		this->pin = expNumber == 1 ? analogPin0 : analogPin1;
		this->expNumber = expNumber;
	}	

	virtual void ChangeExp(short expNumber) {
		this->expNumber = expNumber;
	}

	virtual void OneStep() {
		int newValue = analogPinRead(this->pin) / 32; // 0-4095 => 0-127
		if (oldValue == -1) {
			oldValue = newValue;
			return;
		}

		// Don't send pedal value on first round. Only send if changes
		int diff = newValue - oldValue;
		if (diff >= change_threshold || diff <= -1*change_threshold) {
			oldValue = newValue;
			axeController->sendExpressionPedalValue(this->expNumber, newValue);
		}		
	}
};