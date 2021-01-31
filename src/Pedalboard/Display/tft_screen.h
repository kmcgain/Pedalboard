#pragma once


#include "../../Domain/screen.h"
#include "../../Domain/function/function.h"
#include "../../Domain/function/state/function_state.h"

#include "../../Domain/preset.h"
#include "../../Domain/tuner.h"


//#include <Adafruit_GFX.h> // core graphics library
#include <TFT_eSPI.h>
#include <SPI.h>
//#include "../../libraries/GFrame/gframe.h"

class TftScreen : public Screen {
private:
	// Adafruit_ST7735* screen2;
	//GFrame* screen;
	//TFT_eSPI* screen;
	int screenNumber;
	int cs_pin;

public: 
	TftScreen(byte screenNumber);
	static void GlobalInit();
	virtual void Init();
	virtual void DisplayFunction(FunctionState* functionState, Preset* currentPreset, TunerData& tuner);
	virtual void SetToWrite();
	virtual void SetToNotWrite();	
};