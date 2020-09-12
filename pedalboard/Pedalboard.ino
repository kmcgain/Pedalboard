

#include "src/Domain/layout_manager.h"
#include "src/Domain/interrupt_manager.h"
#include "src/Domain/interrupt_registrar.h"
#include "src/Domain/layout_setup.h"
#include "src/Domain/worker_process.h"
#include "src/Domain/axe_controller.h"
#include "src/Domain/screen_factory.h"

uint32_t lastTime;
WorkerProcess workerProcess;  

void setup() {
  lastTime = millis();
  Serial.begin(9600); 

  Serial.print(F("Setting up\n"));

  
  // Light up the screens
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);

  auto layoutChanger = new LayoutChanger();
  auto axeController = new AxeController();
  axeController->Init();
  registerLayoutManager(new LayoutManager(new FunctionFactory(layoutChanger, axeController), layoutChanger, new ScreenFactory()));
    
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
  if (millis() - lastTime > 1000) {
    lastTime = millis();
    Serial.print(F("Alive\n"));
  }
    
  workerProcess.OneStep();
  Logger::flush();
}
