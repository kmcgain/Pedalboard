
#include <Arduino.h>
#include "control.h"
#include "layout.h"

Layout::Layout(Control*** controls, int rows, int cols){
    this->controls = controls;
    this->rows = rows;
    this->cols = cols;
}

void Layout::init() {
    const int startingPin = (this->rows*this->cols) - 1;
    int d_pin;

    // for (int row = 0; row < this->rows; row++)
    //     for (int col = 0; col < this->cols; col++) {
    //         d_pin = startingPin - row*this->rows - col;        
    //         pinMode(d_pin, INPUT_PULLUP);
    //         control_interrupt_on_press(digitalPinToInterrupt(d_pin), row, col);
    //         control_interrupt_on_release(digitalPinToInterrupt(d_pin));
    //         attachInterrupt(digitalPinToInterrupt(d_pin), &Control::OnPressInterrupt, RISING);
    //         attachInterrupt(digitalPinToInterrupt(d_pin), (void (*)())(&this->controls[row][col].OnRelease), FALLING);                
    //     }

    
}