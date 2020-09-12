#include "tft_screen.h"

#include <Adafruit_GFX.h> // core graphics library
#include <Adafruit_ST7735.h> // hardware-specific library
#include <SPI.h>
#include "../Domain/function/function.h"
#include "../Domain/function/state/function_state.h"

// Due pin 8 is hardwired to SPI RESET
#define rst_pin 8
// A0/DC
#define dc_pin 53

char screen_pins[] = {
	34, 36, 40, 42, 43,
	41, 37, 35, 33, 45,
	48, 47, 46, 49, 44 
};
#define screenToRotate 9

char screenMessage[20];

void sceneSelect(Adafruit_ST7735* screen, FunctionState* state) {
	ScalarFunctionState* st = static_cast<ScalarFunctionState*>(state);

	switch (st->Scalar()) {
	case 1:
		screen->fillScreen(0x641F);
		screen->setTextColor(ST7735_WHITE);
		break;
	case 2:
		screen->fillScreen(0x5BDF);
		screen->setTextColor(ST7735_WHITE);
		break;
	case 3:
		screen->fillScreen(0x537F);
		screen->setTextColor(ST7735_WHITE);
		break;
	case 4:
		screen->fillScreen(0x433F);
		screen->setTextColor(ST7735_WHITE);
		break;
	case 5:
		screen->fillScreen(0x3ADF);
		screen->setTextColor(ST7735_WHITE);
		break;
	case 6:
		screen->fillScreen(0x329F);
		screen->setTextColor(ST7735_WHITE);
		break;
	case 7:
		screen->fillScreen(0x2A3F);
		screen->setTextColor(ST7735_WHITE);
		break;
	case 8:
		screen->fillScreen(0x19FF);
		screen->setTextColor(ST7735_WHITE);
		break;

	}
	screen->setCursor(30, 30);
	screen->setTextSize(4);

	sprintf(screenMessage, "Scene %d", st->Scalar());
	screen->println(screenMessage);

}

void presetCrement(Adafruit_ST7735* screen, FunctionState* state) {
	ScalarFunctionState* st = static_cast<ScalarFunctionState*>(state);

	screen->fillScreen(0x87F0);//GREEN
	screen->setCursor(30, 30);
	screen->setTextSize(4);	
	sprintf(screenMessage, "%s%d Preset", state->Type() == FunctionType::ftPresetDecrement ? F("-") : F("+"), st->Scalar());
	screen->println(screenMessage);
}

TftScreen::TftScreen(char screenNumber) {
	char cs_pin = screen_pins[screenNumber];
	this->screen = new Adafruit_ST7735(cs_pin, dc_pin, rst_pin);

	this->screen->initR(INITR_BLACKTAB);
	if (screenNumber == screenToRotate)
		this->screen->setRotation(3);
	else 
		this->screen->setRotation(1);

	//this->screen->fillScreen(ST7735_RED);
	//this->screen->setTextColor(ST7735_WHITE);

	//this->screen->drawRect(5, 5, 60, 119, ST7735_YELLOW); // upper rectangle
	//this->screen->drawRect(70, 5, 84, 119, ST7735_YELLOW); // lower reactangle
	//this->screen->setCursor(30, 15); // put text in upper rectangle
	//this->screen->setTextSize(2); // select text size
	//this->screen->println(screenNumber);
	//this->screen->setCursor(30, 30);
	//this->screen->println("======");
	//this->screen->setTextSize(2); // select text size
	//this->screen->setCursor(22, 45);
}

void TftScreen::DisplayFunction(FunctionState* functionState) {
	

	switch (functionState->Type()) {
	case FunctionType::ftExpToggle:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->setCursor(30, 30);
		this->screen->setTextSize(4);
		this->screen->println(F("Exp Toggle"));
		break;
	case FunctionType::ftLayoutDecrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->setCursor(30, 30);
		this->screen->setTextSize(4);
		this->screen->println(F("- Layout"));
		break;
	case FunctionType::ftLayoutIncrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->setCursor(30, 30);
		this->screen->setTextSize(4);
		this->screen->println(F("+ Layout"));
		break;		
	case FunctionType::ftLayoutSelect:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->setCursor(30, 30);
		this->screen->setTextSize(4);
		this->screen->println(F("LS"));
		break;
	case FunctionType::ftPresetDecrement:
		presetCrement(this->screen, functionState);
		
		break;
	case FunctionType::ftPresetIncrement:
		presetCrement(this->screen, functionState);

		break;
	case FunctionType::ftSceneDecrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->setCursor(30, 30);
		this->screen->setTextSize(4);
		this->screen->println(F("- Scene"));
		break;
	case FunctionType::ftSceneIncrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->setCursor(30, 30);
		this->screen->setTextSize(4);
		this->screen->println(F("+ Scene"));
		break;
	case FunctionType::ftSceneSelect:
		sceneSelect(this->screen, functionState);
		break;
	case FunctionType::ftTapTempo:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->setCursor(30, 30);
		this->screen->setTextSize(4);
		this->screen->println(F("Tap Tempo"));
		break;
	case FunctionType::ftTunerToggle:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->setCursor(30, 30);
		this->screen->setTextSize(4);
		this->screen->println(F("Tuner"));
		break;
	}
}

