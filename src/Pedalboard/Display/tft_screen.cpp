#include "tft_screen.h"


//#include <Adafruit_GFX.h> // core graphics library
//#include "../libraries/Adafruit_ST7735/Adafruit_ST7735.h" // hardware-specific library
//#include "../../libraries/GFrame/gframe.h"

#include <TFT_eSPI.h>
#include <SPI.h>
#include "../../Domain/function/function.h"
#include "../../Domain/function/state/function_state.h"

#include "../../Domain/logger.h"

#include "../../Domain/pedal_settings.h"

#include "definitions.h"

#include "effect.h"
#include "exp_toggle.h"
#include "helper.h"
#include "layout_select.h"
#include "preset_crement.h"
#include "preset_display.h"
#include "scene_select.h"
#include "tuner.h"
#include "preset_full_select.h"

#include "../../Domain/pedal_settings.h"

char logMessage[80];

TFT_eSPI* screen = new TFT_eSPI();



TftScreen::TftScreen(byte screenNumber) {
	this->screenNumber = screenNumber;
	this->cs_pin = PedalSettings["screenPins"][screenNumber];
	//this->cs_pin = 35;


	//screen = new TFT_eSPI();
	
	//screen->initR(INITR_BLACKTAB);
	if (screenNumber == 7) {
		// TODO: Factor this out?
		//tunerNoteCanvas.setRotation(0); 
	}
	
	pinMode(this->cs_pin, OUTPUT);
	this->SetToNotWrite();
}

void TftScreen::GlobalInit() {
	screen->init(ST7735_BLACKTAB);
	screen->fillScreen(ST7735_BLACK);

	// Just some defaults to prevent crashes if not explicitly set for a screen
	screen->setTextSize(3);
	screen->setTextFont(2);
	screen->setCursor(30, 30);
	screen->setTextColor(ST7735_WHITE);
	screen->setTextWrap(true);
}

void TftScreen::Init() {
	int rotation = PedalSettings["screenRotations"][screenNumber];
	this->SetToWrite();
	screen->setRotation(rotation);	
	this->SetToNotWrite();
}

void TftScreen::SetToWrite() {
	digitalWrite(this->cs_pin, LOW);
}

void TftScreen::SetToNotWrite() {
	digitalWrite(this->cs_pin, HIGH);
}

void TftScreen::DisplayFunction(FunctionState* functionState, Preset* currentPreset, TunerData& tuner) {
	this->SetToWrite();

	if (this->screenNumber == 7) {
		if (tuner.Active) {
			displayTuner(screen, tuner);
			this->SetToNotWrite();
			return;
		}
		else {
			hasCleared = false;
		}
	}


	switch (functionState->Type()) {
	case FunctionType::ftExpToggle:
		expToggle(screen, functionState);		
		break;
	case FunctionType::ftLayoutDecrement:
		screen->fillScreen(TFT_RED);
		screen->setTextColor(TFT_WHITE);
		drawCentreString(screen, "- Layout");
		break;
	case FunctionType::ftLayoutIncrement:
		screen->fillScreen(TFT_RED);
		screen->setTextColor(TFT_WHITE);
		drawCentreString(screen, "+ Layout");
		break;		
	case FunctionType::ftLayoutSelect:
		layoutSelect(screen, functionState);		
		break;
	case FunctionType::ftPresetDecrement:
		presetCrement(screen, functionState);		
		break;
	case FunctionType::ftPresetIncrement:
		presetCrement(screen, functionState);		
		break;
	case FunctionType::ftPresetDisplay:
		presetDisplay(screen, functionState);		
		break;
	case FunctionType::ftPresetFullSelect:
		displayPresetSelect(screen, functionState, this->screenNumber);
		break;
	case FunctionType::ftSceneDecrement:
		screen->fillScreen(TFT_RED);
		screen->setTextColor(TFT_WHITE);
		drawCentreString(screen, "- Scene");
		break;
	case FunctionType::ftSceneIncrement:
		screen->fillScreen(TFT_RED);
		screen->setTextColor(TFT_WHITE);
		drawCentreString(screen, "+ Scene");
		break;
	case FunctionType::ftSceneSelect:
		sceneSelect(screen, functionState, currentPreset);		
		break;
	case FunctionType::ftTapTempo:
		screen->fillScreen(TFT_MAGENTA);
		screen->setTextColor(TFT_WHITE);
		drawCentreString(screen, "Tap");
		break;
	case FunctionType::ftTunerToggle:
		screen->fillScreen(TFT_YELLOW);
		screen->setTextColor(TFT_BLACK);
		drawCentreString(screen, "Tuner");
		break;
	case FunctionType::ftEffect:
		effect(screen, functionState, currentPreset);		
		break;
	case FunctionType::ftMute:
		ToggleFunctionState* st = static_cast<ToggleFunctionState*>(functionState);
		screen->fillScreen(TFT_WHITE);
		screen->setTextColor(TFT_BLACK);
		drawCentreString(screen, st->Current() ? "Mute" : "Unmute");
		break;
	}

	this->SetToNotWrite();
}

