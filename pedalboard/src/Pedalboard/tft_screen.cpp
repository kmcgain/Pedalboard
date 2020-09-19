#include "tft_screen.h"

#include <Adafruit_GFX.h> // core graphics library
#include <Adafruit_ST7735.h> // hardware-specific library
#include <SPI.h>
#include "../Domain/function/function.h"
#include "../Domain/function/state/function_state.h"

#include "../Domain/logger.h"

#define screen_w 160
#define screen_h 128
#define font_w_px 6
#define font_h_px 8
#define border_w 10
#define border_h 10

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


void drawCentreString(Adafruit_ST7735* screen, const char* buf)
{
	// Draw the string to fit on screen
	// Each font is 6x8 * font_size
	auto txtLength = 0;
	while (true) {
		if (buf[txtLength] == '\0')
			break;
		txtLength++;
	}

	Logger::log(txtLength);
	Logger::log("\n");

	// TODO: Have a border in this calc.


	auto maxWidthOfFont = (screen_w - (border_w*2)) / (font_w_px*txtLength); 
	auto maxHeightOfFont = (screen_h - (border_h*2)) / font_h_px;
	auto fontSize = maxWidthOfFont > maxHeightOfFont ? maxHeightOfFont : maxWidthOfFont;

	screen->setTextSize(fontSize);

	auto text_width_px = fontSize * font_w_px * txtLength;
	auto text_height_px = fontSize * font_h_px;
	auto x = (screen_w / 2) - (text_width_px / 2);
	auto y = (screen_h / 2) - (text_height_px / 2);

	screen->setCursor(x, y);
	screen->print(buf);
}

void sceneSelect(Adafruit_ST7735* screen, FunctionState* state, Preset* currentPreset) {
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


	if (currentPreset != nullptr) {
		const char* sName = currentPreset->getSceneName(st->Scalar());
		if (sName != nullptr && sName[0] != '\0') {
			drawCentreString(screen, sName);
			return;
		}
	}

	sprintf(screenMessage, "%d", st->Scalar());
	drawCentreString(screen, screenMessage);	
}

void presetCrement(Adafruit_ST7735* screen, FunctionState* state) {
	ScalarFunctionState* st = static_cast<ScalarFunctionState*>(state);

	screen->fillScreen(0x87F0);//GREEN
	screen->setTextColor(ST7735_BLACK);//black
	sprintf(screenMessage, "%s%d Preset", state->Type() == FunctionType::ftPresetDecrement ? F("-") : F("+"), st->Scalar());
	drawCentreString(screen, screenMessage);
}


void layoutSelect(Adafruit_ST7735* screen, FunctionState* state) {
	ScalarFunctionState* st = static_cast<ScalarFunctionState*>(state);
	screen->fillScreen(ST7735_RED);
	screen->setTextColor(ST7735_WHITE);
	sprintf(screenMessage, "LS %d", st->Scalar());
	drawCentreString(screen, screenMessage);
}

TftScreen::TftScreen(char screenNumber) {
	char cs_pin = screen_pins[screenNumber];
	this->screen = new Adafruit_ST7735(cs_pin, dc_pin, rst_pin);

	this->screen->initR(INITR_BLACKTAB);
	if (screenNumber == screenToRotate)
		this->screen->setRotation(3);
	else 
		this->screen->setRotation(1);
}

void TftScreen::DisplayFunction(FunctionState* functionState, Preset* currentPreset) {
	switch (functionState->Type()) {
	case FunctionType::ftExpToggle:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, "Exp Toggle");
		break;
	case FunctionType::ftLayoutDecrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, "- Layout");
		break;
	case FunctionType::ftLayoutIncrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, "+ Layout");
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
	case FunctionType::ftSceneDecrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, "- Scene");
		break;
	case FunctionType::ftSceneIncrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, "+ Scene");
		break;
	case FunctionType::ftSceneSelect:
		sceneSelect(this->screen, functionState, currentPreset);
		break;
	case FunctionType::ftTapTempo:
		this->screen->fillScreen(ST7735_MAGENTA);
		this->screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, "Tap Tempo");
		break;
	case FunctionType::ftTunerToggle:
		this->screen->fillScreen(ST7735_YELLOW);
		this->screen->setTextColor(ST7735_BLACK);
		drawCentreString(screen, "Tuner");
		break;
	}
}

