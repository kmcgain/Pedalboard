#include "pch.h"

#include "..\src\Domain\interrupt_manager.h"
#include "..\src\Domain\interrupt_registrar.h"

using namespace fakeit;


TEST(InterruptManagerTest, ShouldRegisterInterruptsAvoidingUnwantedPins) {
	reset_interrupts();

	Mock<InterruptRegistrar> interruptRegistrarMock;
	Fake(Method(interruptRegistrarMock, attachDigitalInterrupt));
	Fake(Method(interruptRegistrarMock, inputPullup));
	

	BoardConstants bc = BoardConstants();
	bc.Falling = 1;
	bc.Rising = 2;
	bc.Change = 3;

	InterruptRegistrar & ir = interruptRegistrarMock.get();
	setup_interrupts(&ir, bc);

	Verify(Method(interruptRegistrarMock, attachDigitalInterrupt).Matching([](byte pin, void (*callback)(), byte mode) {return mode == 3 && pin == 24; })).Once();
	Verify(Method(interruptRegistrarMock, attachDigitalInterrupt).Matching([](byte pin, void (*callback)(), byte mode) {return mode == 3 && pin == 2; })).Never();
}