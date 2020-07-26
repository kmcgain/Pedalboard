#pragma once

#ifndef INTERRUPT_REGISTRAR_H
#define INTERRUPT_REGISTRAR_H

class InterruptRegistrar {
public:
	InterruptRegistrar();
	virtual ~InterruptRegistrar();
	virtual void attachDigitalInterrupt(int digitalPin, void (*callback)(), unsigned int mode);
};

#endif