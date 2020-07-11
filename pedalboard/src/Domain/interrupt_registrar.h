#pragma once

class InterruptRegistrar {
public:
	InterruptRegistrar();
	virtual ~InterruptRegistrar();
	virtual void attachDigitalInterrupt(int digitalPin, void (*callback)(), unsigned int mode);
};

