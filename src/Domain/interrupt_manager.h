#pragma once
#ifndef _INTERRUPT_h
#define _INTERRUPT_h

#include "constants.h"
#include "layout_setup.h"
#include "interrupt_registrar.h"

// This is to avoid initial interrupt signals
void start_recording();

template<char N>
void pin_callback_press();

template<char N>
void pin_callback_release();


template<char N>
void define_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, char* interruptPins, char numOfPins);

template<>
void define_interrupts<-1>(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, char* interruptPins, char numOfPins);

void define_interrupt_to_layout(char* interruptPins, char numOfPins);

void reset_interrupts();

void setup_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants);

#endif

