#pragma once

#include "../Domain/screen.h"
#include "../Domain/function/function.h"
#include "../Domain/function/state/function_state.h"

#include <Adafruit_GFX.h> // core graphics library
#include <Adafruit_ST7735.h> // hardware-specific library
#include <SPI.h>

class TftScreen : public Screen {
private:
	Adafruit_ST7735* screen;

public: 
	TftScreen(char screenNumber);
	virtual void DisplayFunction(FunctionState* functionState);
};