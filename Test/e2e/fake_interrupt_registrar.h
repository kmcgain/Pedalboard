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
	virtual void attachDigitalInterrupt(char digitalPin, void (*callback)(), unsigned char mode);
    void fireInterrupt(char digitalPin, char mode);
    virtual void inputPullup(char dwPin);
};

#endif