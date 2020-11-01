

#include "src/Domain/layout_manager.h"
#include "src/Domain/interrupt_manager.h"
#include "src/Domain/interrupt_registrar.h"
#include "src/Domain/layout_setup.h"
#include "src/Domain/worker_process.h"
#include "src/Domain/axe_controller.h"
#include "src/Domain/screen_factory.h"
#include "src/Domain/preset.h"
#include "src/Domain/tuner.h"

#include "generated/settings.h"
#include "src/Domain/pedal_settings.h"

#include <ArduinoJson.h>

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

extern char _end;
extern "C" char *sbrk(int i);
char *ramstart=(char *)0x20070000;
char *ramend=(char *)0x20088000;

#define TAP_TEMPO_LED_PIN 29

uint32_t lastTime;
WorkerProcess* workerProcess;  
volatile unsigned long tapTempoPulseTime = -1;
bool tempoLedOn = false;
Preset* currentPreset = nullptr;
TunerData tuner;
  
void onTapTempo() {
  tapTempoPulseTime = millis();
}

void onPresetChange(Preset* axePreset) {
  currentPreset = axePreset;
}

void onTunerData(const char* note, const short string, const short fineTune) {
  strcpy(tuner.Note, note);
  tuner.FineTune = fineTune;
  tuner.String = string;
}

void setup() {  
  lastTime = millis();
  Serial.begin(9600); 
  while (!Serial);

  Serial.print(F("Setting up\n"));

  analogReadResolution(12);
  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  
  // Light up the screens
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  // Setup tempo led
  pinMode(TAP_TEMPO_LED_PIN, OUTPUT);

  // Load settings
  auto error = deserializeJson(PedalSettings, jsonSettings);
  if (error) {
    Logger::log("Failed to setup due to bad settings");
    return;
  }
  

  auto layoutChanger = new LayoutChanger();
  auto axeController = new AxeController();
  axeController->Init(onTapTempo, onPresetChange, onTunerData);
  auto exp1 = new Expression(1, axeController);
  auto exp2 = new Expression(2, axeController);
  registerLayoutManager(new LayoutManager(new FunctionFactory(layoutChanger, axeController), layoutChanger, new ScreenFactory(), exp1, exp2));
    
  InterruptRegistrar* interruptRegistrar = new InterruptRegistrar();
  BoardConstants boardConstants = BoardConstants();
  boardConstants.Rising = RISING;
  boardConstants.Falling = FALLING;
  boardConstants.Change = CHANGE;

  GetLayoutManager()->init();
  setup_interrupts(interruptRegistrar, boardConstants);  

  workerProcess = new WorkerProcess(axeController, exp1, exp2);

  start_recording();
}

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__
 
int freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}

void printf(const char* fmt, va_list args) {
  char buf[15];
  sprintf(buf, fmt, args);
  Serial.print(buf);
}

void ShowMemory(void)
{
  
  struct mallinfo mi=mallinfo();

  char *heapend=sbrk(0);
  register char * stack_ptr asm("sp");

  printf("Estimated Free RAM: %d\n\n",stack_ptr - heapend + mi.fordblks);
}

void loop() {  
#ifdef DEBUG
  if (millis() - lastTime > 3000) {
    lastTime = millis();
    Logger::log("Alive\n");    
    ShowMemory();
  }
#endif

  if (!tempoLedOn && tapTempoPulseTime != -1) {
    digitalWrite(TAP_TEMPO_LED_PIN, HIGH);
    tempoLedOn = true;
  }

  if (tempoLedOn && tapTempoPulseTime < millis()-50) {
    tapTempoPulseTime = -1;
    digitalWrite(TAP_TEMPO_LED_PIN, LOW);
    tempoLedOn = false;
  }
    
  workerProcess->OneStep(currentPreset, tuner);
  Logger::flush();
}
