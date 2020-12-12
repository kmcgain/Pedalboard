#pragma once
#ifndef _INTERRUPT_h
#define _INTERRUPT_h

#include "constants.h"
#include "layout_setup.h"
#include "interrupt_registrar.h"

// This is to avoid initial interrupt signals
void start_recording();

template<byte N>
void pin_callback_press();

template<byte N>
void pin_callback_release();


template<byte N>
void define_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, byte* interruptPins, byte numOfPins);

template<>
void define_interrupts<-1>(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants, byte* interruptPins, byte numOfPins);

void define_interrupt_to_layout(byte* interruptPins, byte numOfPins);

void reset_interrupts();

void setup_interrupts(InterruptRegistrar* interruptRegistrar, BoardConstants boardConstants);

#endif

