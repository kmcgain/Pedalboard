

#include "src/Domain/layout_manager.h"
#include "src/Domain/interrupt_manager.h"
#include "src/Domain/interrupt_registrar.h"
#include "src/Domain/layout_setup.h"
#include "src/Domain/worker_process.h"
#include "src/Domain/axe_controller.h"
#include "src/Domain/screen_factory.h"
#include "src/Domain/preset.h"

#define TAP_TEMPO_LED_PIN 31

uint32_t lastTime;
WorkerProcess* workerProcess;  
volatile unsigned long tapTempoPulseTime = -1;
bool tempoLedOn = false;
Preset* currentPreset = nullptr;

void onTapTempo() {
  tapTempoPulseTime = millis();
}

void onPresetChange(Preset* axePreset) {
  currentPreset = axePreset;
}

void setup() {
  lastTime = millis();
  Serial.begin(9600); 
  while (!Serial);

  Serial.print(F("Setting up\n"));

  
  // Light up the screens
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);

  // Setup tempo led
  pinMode(TAP_TEMPO_LED_PIN, OUTPUT);
  

  auto layoutChanger = new LayoutChanger();
  auto axeController = new AxeController();
  axeController->Init(onTapTempo, onPresetChange);
  registerLayoutManager(new LayoutManager(new FunctionFactory(layoutChanger, axeController), layoutChanger, new ScreenFactory()));
    
  InterruptRegistrar* interruptRegistrar = new InterruptRegistrar();
  BoardConstants boardConstants = BoardConstants();
  boardConstants.Rising = RISING;
  boardConstants.Falling = FALLING;
  boardConstants.Change = CHANGE;

  GetLayoutManager()->init();
  setup_interrupts(interruptRegistrar, boardConstants);  

  workerProcess = new WorkerProcess(axeController);

  start_recording();
}


void loop() {  
  if (millis() - lastTime > 1000) {
    lastTime = millis();
    Logger::log("Alive\n");    
  }

  if (!tempoLedOn && tapTempoPulseTime != -1) {
    digitalWrite(TAP_TEMPO_LED_PIN, HIGH);
    tempoLedOn = true;
  }

  if (tempoLedOn && tapTempoPulseTime < millis()-50) {
    tapTempoPulseTime = -1;
    digitalWrite(TAP_TEMPO_LED_PIN, LOW);
    tempoLedOn = false;
  }
    
  workerProcess->OneStep(currentPreset);
  Logger::flush();
}
