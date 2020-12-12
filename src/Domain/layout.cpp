#include "pch.h"
#include "control.h"
#include "layout.h"

Layout::Layout(Control*** controls, byte rows, byte cols){
    this->controls = controls;
    this->rows = rows;
    this->cols = cols;
}

Layout::~Layout() {
    for (byte i = 0; i < this->rows; i++)
        for (byte j = 0; j < this->cols; j++)
            delete this->controls[i][j];
    delete this->controls;
}

void Layout::init() {
}

void Layout::Exit(){}

void Layout::Invalidate() {
    for (byte i = 0; i < this->rows; i++)
        for (byte j = 0; j < this->cols; j++)
            this->controls[i][j]->Invalidate();
}


void Layout::ProcessOutstanding() {    
    for (byte i = 0; i < this->rows; i++)
        for (byte j = 0; j < this->cols; j++) {
            this->controls[i][j]->HandleState();
        }
}

void Layout::PrintDebug() {
    for (byte i = 0; i < this->rows; i++)
        for (byte j = 0; j < this->cols; j++) {
            if (i == 0 && j == 2)
                this->controls[i][j]->PrintDebug();
        }
}

void Layout::RefreshScreens(Preset* currentPreset, TunerData& tuner) {
    for (byte i = 0; i < this->rows; i++)
        for (byte j = 0; j < this->cols; j++)
            this->controls[i][j]->RefreshScreen(currentPreset, tuner);
}