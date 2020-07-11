//#include <Arduino.h>
//#include <AxeFxControl.h>
//#include "src/function.h"
//#include "src/function_impl.h"
//#include "src/layout_definition.h"
//
//#include "Pedalboard/time_record.h"
#include "src/Domain/layout_manager.h"
#include "src/Domain/interrupt_manager.h"
#include "src/Domain/interrupt_registrar.h"
#include "src/Domain/layout_setup.h"
//#include <Pedalboard/Pedalboard.Domain/layout_setup.h>
//#include <Pedalboard.Domain/interrupt.h>

void setup() {
	registerLayoutManager(new LayoutManager(new FunctionFactory(new LayoutChanger())));

	InterruptRegistrar* interruptRegistrar = new InterruptRegistrar();
	BoardConstants boardConstants = BoardConstants();
	boardConstants.Rising = RISING;
	boardConstants.Falling = RISING;
	setup_interrupts(interruptRegistrar, boardConstants);
	GetLayoutManager()->init();
}

void loop() {
	// put your main code here, to run repeatedly:

}