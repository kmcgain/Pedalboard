#include "constants.h"
#include "layout_setup.h"
#include "interrupt_registrar.h"
#include "logger.h"
#include "pin.h"
#include "pedal_settings.h"

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

template<byte N>
void define_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, byte* interruptPins, byte numOfPins) {
    bool included = false;
    for (byte i = 0; i < numOfPins; i++)
        if (interruptPins[i] == N)
            included = true;

    if (included) { 
        interruptRegistrar->inputPullup(N);
                
        interruptRegistrar->attachDigitalInterrupt(N, pin_callback_change<N>, boardConstants.Change);
    }

    define_interrupts<N - 1>(interruptRegistrar, boardConstants, interruptPins, numOfPins);
}

template<>
void define_interrupts<-1>(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, byte* interruptPins, byte numOfPins) {
    // No-op
}

void define_interrupt_to_layout(byte* interruptPins, byte numOfPins) {
    for (byte i = 0; i <= MAX_DIGITAL_PIN; i++) {
        pinToCol[i] = -1;
        pinToRow[i] = -1;
    }

    for (byte i = 0; i < numOfPins; i++) {
        byte pinNum = interruptPins[i];
        pinToCol[pinNum] = i % FS_COLS;
        pinToRow[pinNum] = i / FS_COLS; 
    }
}

void reset_interrupts() {
    for (byte i = 0; i <= MAX_DIGITAL_PIN; i++)
        pinToRow[i] = 0;
}

void setup_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants) {
    byte numPins = PedalSettings["buttonPins"].size();
    byte* buttonPins = (byte*)malloc(sizeof(byte)*numPins);
    for (auto i = 0; i < numPins; i++) {
        buttonPins[i] = PedalSettings["buttonPins"][i];
    }
    define_interrupt_to_layout(buttonPins, numPins);
    define_interrupts<MAX_DIGITAL_PIN>(interruptRegistrar, boardConstants, buttonPins, numPins);

    delete buttonPins;
}
