#pragma once

#include "../Domain/screen.h"
#include "../Domain/function/function.h"
#include "../Domain/function/state/function_state.h"

#include "../Domain/preset.h"
#include "../Domain/tuner.h"

#include <Adafruit_GFX.h> // core graphics library
#include "../libraries/Adafruit_ST7735/Adafruit_ST7735.h" // hardware-specific library
#include <SPI.h>
#include "gframe.h"

class TftScreen : public Screen {
private:
	// Adafruit_ST7735* screen2;
	GFrame* screen;
	int screenNumber;

public: 
	TftScreen(char screenNumber);
	virtual void DisplayFunction(FunctionState* functionState, Preset* currentPreset, TunerData& tuner);
};