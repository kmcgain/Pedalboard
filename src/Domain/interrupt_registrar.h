#pragma once

#ifndef INTERRUPT_REGISTRAR_H
#define INTERRUPT_REGISTRAR_H

class InterruptRegistrar {
public:
	InterruptRegistrar();
	virtual ~InterruptRegistrar();
	virtual void attachDigitalInterrupt(char digitalPin, void (*callback)(), unsigned char mode);
	virtual void inputPullup(char dwPin);
};

#endif