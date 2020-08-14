#include "src/Domain/layout_manager.h"
#include "src/Domain/interrupt_manager.h"
#include "src/Domain/interrupt_registrar.h"
#include "src/Domain/layout_setup.h"
#include "src/Domain/worker_process.h"
#include "src/Domain/axe_controller.h"


uint32_t lastTime;

void setup() {
  lastTime = millis();
  Serial.begin(9600); 

  Serial.print("Setting up\n");
  
  registerLayoutManager(new LayoutManager(new FunctionFactory(new LayoutChanger(), new AxeController())));

  InterruptRegistrar* interruptRegistrar = new InterruptRegistrar();
  BoardConstants boardConstants = BoardConstants();
  boardConstants.Rising = RISING;
  boardConstants.Falling = FALLING;

  GetLayoutManager()->init();
  setup_interrupts(interruptRegistrar, boardConstants);  
}


void loop() {
  if (millis() - lastTime > 1000) {
    lastTime = millis();
    Serial.print("Alive\n");
  }
  return;
  WorkerProcess workerProcess;
  workerProcess.OneStep();
}
