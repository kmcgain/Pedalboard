#include "tft_screen.h"

#include <Adafruit_GFX.h> // core graphics library
#include <Adafruit_ST7735.h> // hardware-specific library
#include <SPI.h>
#include "../Domain/function/function.h"

// Due pin 8 is hardwired to SPI RESET
#define rst_pin 8
// A0/DC
#define dc_pin 53

int screen_pins[] = { 
	34, 36, 40, 42, 43,
	41, 37, 35, 33, 45,
	48, 47, 46, 49, 44 
};

TftScreen::TftScreen(int screenNumber) {
	int cs_pin = screen_pins[screenNumber];
	this->screen = new Adafruit_ST7735(cs_pin, dc_pin, rst_pin);

	this->screen->initR(INITR_BLACKTAB);
	this->screen->fillScreen(ST7735_RED);
	this->screen->setTextColor(ST7735_WHITE);

	this->screen->drawRect(5, 5, 119, 60, ST7735_YELLOW); // upper rectangle
	this->screen->drawRect(5, 70, 119, 84, ST7735_YELLOW); // lower reactangle
	this->screen->setCursor(30, 15); // put text in upper rectangle
	this->screen->setTextSize(2); // select text size
	this->screen->println(screenNumber);
	this->screen->setCursor(30, 30);
	this->screen->println("======");
	this->screen->setTextSize(2); // select text size
	this->screen->setCursor(22, 45);
}

void TftScreen::DisplayFunction(const Function::FunctionType functionType) {
	return;
	this->screen->setCursor(30, 30);
	this->screen->setTextSize(4);

	switch (functionType) {
	case Function::FunctionType::expToggle:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->println("Exp Toggle");
		return;
	case Function::FunctionType::layoutDecrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->println("- Layout");

		return;
	case Function::FunctionType::layoutIncrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->println("+ Layout");

		return;
	case Function::FunctionType::layoutSelect:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->println("LS");

	case Function::FunctionType::presetDecrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->println("- Preset");

	case Function::FunctionType::presetIncrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->println("+ Preset");

	case Function::FunctionType::sceneDecrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->println("- Scene");

	case Function::FunctionType::sceneIncrement:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->println("+ Scene");

	case Function::FunctionType::sceneSelect:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->println("Scene Select");

	case Function::FunctionType::tapTempo:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->println("Tap Tempo");

	case Function::FunctionType::tunerToggle:
		this->screen->fillScreen(ST7735_RED);
		this->screen->setTextColor(ST7735_WHITE);
		this->screen->println("Tuner");

	}
}
