#include "pch.h"

#include "..\src\Domain\interrupt_manager.h"
#include "..\src\Domain\interrupt_registrar.h"

using namespace fakeit;


TEST(InterruptManagerTest, ShouldRegisterInterruptsAvoidingUnwantedPins) {
	reset_interrupts();

	Mock<InterruptRegistrar> interruptRegistrarMock;
	Fake(Method(interruptRegistrarMock, attachDigitalInterrupt));
	

	BoardConstants bc = BoardConstants();
	bc.Falling = 1;
	bc.Rising = 2;

	InterruptRegistrar & ir = interruptRegistrarMock.get();
	setup_interrupts(&ir, bc);

	Verify(Method(interruptRegistrarMock, attachDigitalInterrupt).Matching([](int pin, void (*callback)(), unsigned int mode) {return mode == 1 && pin == 25; })).Never();
	Verify(Method(interruptRegistrarMock, attachDigitalInterrupt).Matching([](int pin, void (*callback)(), unsigned int mode) {return mode == 2 && pin == 25; })).Never();
	Verify(Method(interruptRegistrarMock, attachDigitalInterrupt).Matching([](int pin, void (*callback)(), unsigned int mode) {return mode == 1 && pin == 24; })).Once();
	Verify(Method(interruptRegistrarMock, attachDigitalInterrupt).Matching([](int pin, void (*callback)(), unsigned int mode) {return mode == 2 && pin == 24; })).Once();
	Verify(Method(interruptRegistrarMock, attachDigitalInterrupt).Matching([](int pin, void (*callback)(), unsigned int mode) {return mode == 1 && pin == 2; })).Once();
	Verify(Method(interruptRegistrarMock, attachDigitalInterrupt).Matching([](int pin, void (*callback)(), unsigned int mode) {return mode == 2 && pin == 2; })).Once();
}