#pragma once

#include "../../Domain/screen.h"
#include "../../Domain/function/function.h"
#include "../../Domain/function/state/function_state.h"

#include "../../Domain/preset.h"
#include "../../Domain/tuner.h"

#include <Adafruit_GFX.h> // core graphics library
#include <SPI.h>
#include "../../libraries/GFrame/gframe.h"

class TftScreen : public Screen {
private:
	// Adafruit_ST7735* screen2;
	GFrame* screen;
	int screenNumber;

public: 
	TftScreen(byte screenNumber);
	virtual void DisplayFunction(FunctionState* functionState, Preset* currentPreset, TunerData& tuner);
};