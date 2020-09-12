#include "pch.h"
#include "control.h"
#include "layout.h"

Layout::Layout(Control*** controls, char rows, char cols){
    this->controls = controls;
    this->rows = rows;
    this->cols = cols;
}

Layout::~Layout() {
    for (char i = 0; i < this->rows; i++)
        for (char j = 0; j < this->cols; j++)
            delete this->controls[i][j];
    delete this->controls;
}

void Layout::init() {
   // const char startingPin = (this->rows*this->cols) - 1;
    //char d_pin;

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

void Layout::Exit(){}


void Layout::ProcessOutstanding() {    
    for (char i = 0; i < this->rows; i++)
        for (char j = 0; j < this->cols; j++) {
            this->controls[i][j]->HandleState();
        }
}

void Layout::PrintDebug() {
    for (char i = 0; i < this->rows; i++)
        for (char j = 0; j < this->cols; j++) {
            if (i == 0 && j == 2)
                this->controls[i][j]->PrintDebug();
        }
}

void Layout::RefreshScreens() {
    for (char i = 0; i < this->rows; i++)
        for (char j = 0; j < this->cols; j++)
            this->controls[i][j]->RefreshScreen();
}