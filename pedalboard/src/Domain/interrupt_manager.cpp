#include "constants.h"
#include "layout_setup.h"
#include "interrupt_registrar.h"
#include "logger.h"
#include "pin.h"

int unavailable_pins[] = { 0,1,4,10,14,15,16,17,18,19,20,21,52 };

int pinToRow[MAX_DIGITAL_PIN+1];
int pinToCol[MAX_DIGITAL_PIN+1];
bool recording = false;

void start_recording() {
    recording = true;
}

template<int N>
void pin_callback_change() {
    if (!recording)
        return;

    char dat[50];
    if (!digitalPinHigh(N)) {
        GetLayoutManager()->OnPress(pinToRow[N], pinToCol[N]);
    }
    else {
        GetLayoutManager()->OnRelease(pinToRow[N], pinToCol[N]);
    }
}

template<int N>
void define_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, int* interruptPins, int numOfPins) {
    bool included = false;
    for (int i = 0; i < numOfPins; i++)
        if (interruptPins[i] == N)
            included = true;

    if (included) { 
        interruptRegistrar->inputPullup(N);
        
        
        interruptRegistrar->attachDigitalInterrupt(N, pin_callback_change<N>, boardConstants.Change);
    }

    define_interrupts<N - 1>(interruptRegistrar, boardConstants, interruptPins, numOfPins);
}

template<>
void define_interrupts<-1>(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, int* interruptPins, int numOfPins) {
    // No-op
}

void define_interrupt_to_layout(int* interruptPins, int numOfPins) {
    for (int i = 0; i <= MAX_DIGITAL_PIN; i++) {
        pinToCol[i] = -1;
        pinToRow[i] = -1;
    }

    for (int i = 0; i < numOfPins; i++) {
        int pinNum = interruptPins[i];
        pinToCol[pinNum] = i % FS_COLS;
        pinToRow[pinNum] = i / FS_COLS; 
    }
}

void reset_interrupts() {
    for (int i = 0; i <= MAX_DIGITAL_PIN; i++)
        pinToRow[i] = 0;
}

void setup_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants) {
    // Don't use 4,10,52 for inputs - 10 puts into SPI slave mode. Pin 2 for PWM screen brightness
    int buttonPins[] = { 3,5,6,7,8,9,11,12,13,22,23,24,25,26,27 }; 
    int numPins = sizeof(buttonPins) / sizeof(int);    
    
    define_interrupt_to_layout(buttonPins, numPins);
    define_interrupts<MAX_DIGITAL_PIN>(interruptRegistrar, boardConstants, buttonPins, numPins);        
}
