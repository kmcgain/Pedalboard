#pragma once

#ifndef INTERRUPT_REGISTRAR_H
#define INTERRUPT_REGISTRAR_H

#include "pch.h"

class InterruptRegistrar {
public:
	InterruptRegistrar();
	virtual ~InterruptRegistrar();
	virtual void attachDigitalInterrupt(byte digitalPin, void (*callback)(), byte mode);
	virtual void inputPullup(byte dwPin);
};

#endif