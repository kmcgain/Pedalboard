
#include <Arduino.h>
#include "control.h"

class Layout {    
    private:
        Control** controls;
        size_t rows, cols;

    public:
        Layout(Control** controls, size_t rows, size_t cols){
            this->controls = controls;
            this->rows = rows;
            this->cols = cols;
        }

        void init() {
            const int startingPin = (this->rows*this->cols) - 1;
            int d_pin;

            for (int row = 0; row < this->rows; row++)
                for (int col = 0; col < this->cols; col++) {
                    d_pin = startingPin - row*this->rows - col;        
                    pinMode(d_pin, INPUT_PULLUP);
                    attachInterrupt(digitalPinToInterrupt(d_pin), (void (*)())(&this->controls[row][col].OnPress), RISING);
                    attachInterrupt(digitalPinToInterrupt(d_pin), (void (*)())(&this->controls[row][col].OnRelease), FALLING);                
                }

            
        }
};