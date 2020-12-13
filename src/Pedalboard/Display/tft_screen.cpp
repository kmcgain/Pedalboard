#include "tft_screen.h"

#include <Adafruit_GFX.h> // core graphics library
//#include "../libraries/Adafruit_ST7735/Adafruit_ST7735.h" // hardware-specific library
#include "../../libraries/GFrame/gframe.h"
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

#include "../../libraries/GFrame/Fonts/FreeSans24pt7b.h"

char logMessage[80];





TftScreen::TftScreen(byte screenNumber) {
	this->screenNumber = screenNumber;
	byte cs_pin = PedalSettings["screenPins"][screenNumber];
	this->screen = new GFrame(cs_pin, dc_pin, rst_pin);
	
	this->screen->initR(INITR_BLACKTAB);
	if (screenNumber == 7) {
		// TODO: Factor this out?
		tunerNoteCanvas.setRotation(0); 
	}
	
	int rotation = PedalSettings["screenRotations"][screenNumber];
	this->screen->setRotation(rotation);	
	this->screen->setFont(&FreeSans24pt7b);
}

void TftScreen::DisplayFunction(FunctionState* functionState, Preset* currentPreset, TunerData& tuner) {
	
	sprintf(logMessage, "Drawing for screen: %d Type: %d\n", this->screenNumber, functionState->Type());
	Logger::log(logMessage);
	

	if (this->screenNumber == 7) {
		if (tuner.Active) {
			displayTuner(screen, tuner);
			return;
		}
		else {
			hasCleared = false;
		}
	}


	switch (functionState->Type()) {
	case FunctionType::ftExpToggle:
		expToggle(this->screen, functionState);		
		break;
	case FunctionType::ftLayoutDecrement:
		this->screen->beginDraw();
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, "- Layout");
		this->screen->endDraw();
		break;
	case FunctionType::ftLayoutIncrement:
		this->screen->beginDraw();
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, "+ Layout");
		this->screen->endDraw();
		break;		
	case FunctionType::ftLayoutSelect:
		layoutSelect(this->screen, functionState);		
		break;
	case FunctionType::ftPresetDecrement:
		presetCrement(this->screen, functionState);		
		break;
	case FunctionType::ftPresetIncrement:
		presetCrement(this->screen, functionState);		
		break;
	case FunctionType::ftPresetDisplay:
		presetDisplay(this->screen, functionState);		
		break;
	case FunctionType::ftPresetFullSelect:
		displayPresetSelect(screen, functionState, this->screenNumber);
		break;
	case FunctionType::ftSceneDecrement:
		this->screen->beginDraw();
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, "- Scene");
		this->screen->endDraw();
		break;
	case FunctionType::ftSceneIncrement:
		this->screen->beginDraw();
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, "+ Scene");
		this->screen->endDraw();
		break;
	case FunctionType::ftSceneSelect:
		sceneSelect(this->screen, functionState, currentPreset);		
		break;
	case FunctionType::ftTapTempo:
		this->screen->beginDraw();
		this->screen->fillScreen(ST7735_MAGENTA);
		this->screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, "Tap");
		this->screen->endDraw();
		break;
	case FunctionType::ftTunerToggle:
		this->screen->beginDraw();
		this->screen->fillScreen(ST7735_YELLOW);
		this->screen->setTextColor(ST7735_BLACK);
		drawCentreString(screen, "Tuner");
		this->screen->endDraw();
		break;
	case FunctionType::ftEffect:
		effect(this->screen, functionState, currentPreset);		
		break;
	case FunctionType::ftMute:
		this->screen->beginDraw();
		ToggleFunctionState* st = static_cast<ToggleFunctionState*>(functionState);
		this->screen->fillScreen(ST7735_WHITE);
		this->screen->setTextColor(ST7735_BLACK);
		drawCentreString(screen, st->Current() ? "Mute" : "Unmute");
		this->screen->endDraw();
		break;
	}
}

