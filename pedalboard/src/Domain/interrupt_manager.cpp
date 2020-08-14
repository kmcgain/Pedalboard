#include "constants.h"
#include "layout_setup.h"
#include "interrupt_registrar.h"
#include "logger.h"

int unavailable_pins[] = { 0,1,14,15,16,17,18,19,20,21 };

int pinToRow[MAX_DIGITAL_PIN+1];
int pinToCol[MAX_DIGITAL_PIN+1];

template<int N>
void pin_callback_press() {
    GetLayoutManager()->OnPress(pinToRow[N], pinToCol[N]);
}

template<int N>
void pin_callback_release() {
    GetLayoutManager()->OnRelease(pinToRow[N], pinToCol[N]);
}

template<int N>
void define_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, int* interruptPins, int numOfPins) {
    bool included = false;
    for (int i = 0; i < numOfPins; i++)
        if (interruptPins[i] == N)
            included = true;

    if (included) { 
        interruptRegistrar->inputPullup(N);
        interruptRegistrar->attachDigitalInterrupt(N, pin_callback_press<N>, boardConstants.Rising);
        interruptRegistrar->attachDigitalInterrupt(N, pin_callback_release<N>, boardConstants.Falling);
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
    int buttonPins[] = {2};
    //int buttonPins[] = { 2,3,4,5,6,7,8,9,10,11,12,13,22,23,24 };
    int numPins = sizeof(buttonPins) / sizeof(int);    
    
    define_interrupt_to_layout(buttonPins, numPins);
    define_interrupts<MAX_DIGITAL_PIN>(interruptRegistrar, boardConstants, buttonPins, numPins);        
}
