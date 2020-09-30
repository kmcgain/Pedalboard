#ifndef FAKE_INTERRUPT_REGISTRAR_H
#define FAKE_INTERRUPT_REGISTRAR_H

#include "../../src/Domain/interrupt_registrar.h"
#include "../../src/Domain/constants.h"

typedef void (*interruptCb)();

class FakeInterruptRegistrar : public InterruptRegistrar {

private:
    BoardConstants bc;
    interruptCb risingCallbacks[54];
    interruptCb fallingCallbacks[54];

public:
	FakeInterruptRegistrar(BoardConstants& bc);
	virtual ~FakeInterruptRegistrar();
	virtual void attachDigitalInterrupt(int digitalPin, void (*callback)(), unsigned int mode);
    void fireInterrupt(int digitalPin, int mode);
    virtual void inputPullup(int dwPin);
};

#endif