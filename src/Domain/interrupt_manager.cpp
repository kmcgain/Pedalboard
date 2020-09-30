#include "constants.h"
#include "layout_setup.h"
#include "interrupt_registrar.h"
#include "logger.h"
#include "pin.h"

char pinToRow[MAX_DIGITAL_PIN+1];
char pinToCol[MAX_DIGITAL_PIN+1];
bool recording = false;

void start_recording() {
    recording = true;
}

template<int N>
void pin_callback_change() {
    if (!recording)
        return;

    if (!digitalPinHigh(N)) {
        GetLayoutManager()->OnPress(pinToRow[N], pinToCol[N]);
    }
    else {
        GetLayoutManager()->OnRelease(pinToRow[N], pinToCol[N]);
    }
}

template<char N>
void define_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, char* interruptPins, char numOfPins) {
    bool included = false;
    for (char i = 0; i < numOfPins; i++)
        if (interruptPins[i] == N)
            included = true;

    if (included) { 
        interruptRegistrar->inputPullup(N);
        
        
        interruptRegistrar->attachDigitalInterrupt(N, pin_callback_change<N>, boardConstants.Change);
    }

    define_interrupts<N - 1>(interruptRegistrar, boardConstants, interruptPins, numOfPins);
}

template<>
void define_interrupts<-1>(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, char* interruptPins, char numOfPins) {
    // No-op
}

void define_interrupt_to_layout(char* interruptPins, char numOfPins) {
    for (char i = 0; i <= MAX_DIGITAL_PIN; i++) {
        pinToCol[i] = -1;
        pinToRow[i] = -1;
    }

    for (char i = 0; i < numOfPins; i++) {
        char pinNum = interruptPins[i];
        pinToCol[pinNum] = i % FS_COLS;
        pinToRow[pinNum] = i / FS_COLS; 
    }
}

void reset_interrupts() {
    for (char i = 0; i <= MAX_DIGITAL_PIN; i++)
        pinToRow[i] = 0;
}

void setup_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants) {
    // Don't use 4,10,52 for inputs - 10 puts into SPI slave mode. Pin 2 for PWM screen brightness
    // 8 interfere with spi reset?
    char buttonPins[] = {
        3,  5,  6,  7,  9, 
        22, 11, 12, 13, 24, 
        27, 26, 25, 28, 23 
    };
    char numPins = sizeof(buttonPins) / sizeof(char);
    
    define_interrupt_to_layout(buttonPins, numPins);
    define_interrupts<MAX_DIGITAL_PIN>(interruptRegistrar, boardConstants, buttonPins, numPins);        
}
