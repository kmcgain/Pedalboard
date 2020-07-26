#include "src/Domain/layout_manager.h"
#include "src/Domain/interrupt_manager.h"
#include "../../src/Domain/interrupt_manager.cpp"
#include "src/Domain/interrupt_registrar.h"
#include "src/Domain/layout_setup.h"
#include "src/Domain/worker_process.h"

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
	WorkerProcess workerProcess;
	workerProcess.OneStep();
}