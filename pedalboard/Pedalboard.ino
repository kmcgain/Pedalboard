

#include "src/Domain/layout_manager.h"
#include "src/Domain/interrupt_manager.h"
#include "src/Domain/interrupt_registrar.h"
#include "src/Domain/layout_setup.h"
#include "src/Domain/worker_process.h"
#include "src/Domain/axe_controller.h"


uint32_t lastTime;
WorkerProcess workerProcess;

void setup() {
  lastTime = millis();
  Serial.begin(9600); 

  Serial.print("Setting up\n");

  auto layoutChanger = new LayoutChanger();
  registerLayoutManager(new LayoutManager(new FunctionFactory(layoutChanger, new AxeController()), layoutChanger));

  InterruptRegistrar* interruptRegistrar = new InterruptRegistrar();
  BoardConstants boardConstants = BoardConstants();
  boardConstants.Rising = RISING;
  boardConstants.Falling = FALLING;
  boardConstants.Change = CHANGE;

  GetLayoutManager()->init();
  setup_interrupts(interruptRegistrar, boardConstants);  

  start_recording();
}


void loop() {  
  if (millis() - lastTime > 5000) {
    lastTime = millis();
    Serial.print("Alive\n");
    //workerProcess.PrintDebug();
    workerProcess.OneStep();

    Logger::flush();
  }
    
  //workerProcess.OneStep();
}
