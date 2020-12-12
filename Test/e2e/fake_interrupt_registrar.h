#ifndef FAKE_INTERRUPT_REGISTRAR_H
#define FAKE_INTERRUPT_REGISTRAR_H

#include "../../src/Domain/interrupt_registrar.h"
#include "../../src/Domain/constants.h"

typedef void (*interruptCb)();

class FakeInterruptRegistrar : public InterruptRegistrar {

private:
    BoardConstants bc;
    interruptCb changingCallbacks[54];

public:
	FakeInterruptRegistrar(BoardConstants& bc);
	virtual ~FakeInterruptRegistrar();
	virtual void attachDigitalInterrupt(byte digitalPin, void (*callback)(), byte mode);
    void fireInterrupt(byte digitalPin, byte mode);
    virtual void inputPullup(byte dwPin);
};

#endif