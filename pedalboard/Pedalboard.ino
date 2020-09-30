

#include "src/Domain/layout_manager.h"
#include "src/Domain/interrupt_manager.h"
#include "src/Domain/interrupt_registrar.h"
#include "src/Domain/layout_setup.h"
#include "src/Domain/worker_process.h"
#include "src/Domain/axe_controller.h"
#include "src/Domain/screen_factory.h"
#include "src/Domain/preset.h"

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

  analogReadResolution(12);
  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  
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

  /*printf("    arena=%d\n",mi.arena);
  printf("  ordblks=%d\n",mi.ordblks);
  printf(" uordblks=%d\n",mi.uordblks);
  printf(" fordblks=%d\n",mi.fordblks);
  printf(" keepcost=%d\n",mi.keepcost);
  
  printf("RAM Start %lx\n", (unsigned long)ramstart);
  printf("Data/Bss end %lx\n", (unsigned long)&_end);
  printf("Heap End %lx\n", (unsigned long)heapend);
  printf("Stack Ptr %lx\n",(unsigned long)stack_ptr);
  printf("RAM End %lx\n", (unsigned long)ramend);

  printf("Heap RAM Used: %d\n",mi.uordblks);
  printf("Program RAM Used %d\n",&_end - ramstart);
  printf("Stack RAM Used %d\n",ramend - stack_ptr);*/

  printf("Estimated Free RAM: %d\n\n",stack_ptr - heapend + mi.fordblks);
}

void loop() {  
  if (millis() - lastTime > 1000) {
    lastTime = millis();
    Logger::log("Alive\n");    
    ShowMemory();
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
