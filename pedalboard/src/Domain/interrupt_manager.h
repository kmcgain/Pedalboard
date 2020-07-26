#pragma once
#ifndef _INTERRUPT_h
#define _INTERRUPT_h

#include "constants.h"
#include "layout_setup.h"
#include "interrupt_registrar.h"

template<int N>
void pin_callback_press();

template<int N>
void pin_callback_release();


template<int N>
void define_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, int* interruptPins, int numOfPins);

template<>
void define_interrupts<-1>(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, int* interruptPins, int numOfPins);

void define_interrupt_to_layout(int* interruptPins, int numOfPins);

void reset_interrupts();

void setup_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants);

#endif

