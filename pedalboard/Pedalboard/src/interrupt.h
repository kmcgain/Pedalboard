// interrupt.h

#ifndef _INTERRUPT_h
#define _INTERRUPT_h

#include "constants.h"
#include "layout_setup.h"


int unavailable_pins[] = { 0,1,14,15,16,17,18,19,20,21 };


/*
 * INTERRUPTS
 */

int pinToRow[MAX_DIGITAL_PIN];
int pinToCol[MAX_DIGITAL_PIN];

template<typename T>
void pin_callback_press() {
	layoutMgr->OnPress(pinToRow[10], pinToCol[10]);
}

template<int N>
void pin_callback_press() {
    layoutMgr->OnPress(pinToRow[N], pinToCol[N]);
}

template<int N>
void pin_callback_release() {
    layoutMgr->OnRelease(pinToRow[N], pinToCol[N]);
}


template<int N>
void define_interrupts() {
    attachInterrupt(digitalPinToInterrupt(N), &pin_callback_press<N>, FALLING);
    attachInterrupt(digitalPinToInterrupt(N), &pin_callback_release<N>, RISING);

    define_interrupts<N - 1>();
}

template<>
void define_interrupts<0>() {
    // No-op
}

bool available_pin(int pin) {
    int num_unavailable_pins = *(&unavailable_pins + 1) - unavailable_pins;
    for (int i = 0; i < num_unavailable_pins; i++) {
        if (unavailable_pins[i] == pin)
            return false;
    }
    return true;
}

void define_interrupt_to_layout() {
    int next_pin = 0;
    for (int row = 0; row < FS_ROWS; row++) {
        for (int col = 0; col < FS_COLS; col++) {
            while (!available_pin) {
                pinToRow[next_pin++] = -1;
                pinToCol[next_pin] = -1;
            };
            pinToRow[next_pin++] = row;
            pinToCol[next_pin] = col;
        }
    }
}

void setup_interrupts() {
    define_interrupts<MAX_DIGITAL_PIN>();
    define_interrupt_to_layout();

    layoutMgr->OnPress(0, 0);
}


#endif

