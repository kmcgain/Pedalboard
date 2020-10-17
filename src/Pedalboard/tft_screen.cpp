#include "tft_screen.h"

#include <Adafruit_GFX.h> // core graphics library
#include "../libraries/Adafruit_ST7735/Adafruit_ST7735.h" // hardware-specific library
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

byte screen_pins[] = {
	34, 36, 40, 42, 43,
	41, 37, 35, 33, 45,
	48, 47, 46, 49, 44 
};
#define screenToRotate 9


char screenMessage[50];
char logMessage[80];

void lengthOfLongestWord(const char* buf, byte& longestLength, byte& numWords) {
	byte currentLen = 0;
	byte index = 0;
	numWords = 1;
	longestLength = 0;

	while (true) {
		if (buf[index] == '\0')
			break;

		if (buf[index] == ' ' || buf[index] == '\n') {
			numWords++;
			if (currentLen > longestLength)
				longestLength = currentLen;
			currentLen = 0;
		}
		else
			currentLen++;

		index++;
	}

	if (currentLen > longestLength)
		longestLength = currentLen;
}

void drawCentreString(Adafruit_ST7735* screen, const char* buf, int yOffset = 0)
{
	// Draw the string to fit on screen
	// Each font is 6x8 * font_size
	byte txtLength, numWords;
	lengthOfLongestWord(buf, txtLength, numWords);

	auto absYOffset = yOffset > 0 ? yOffset : -1*yOffset;

	auto maxWidthOfFont = (screen_w - (border_w*2)) / (font_w_px*txtLength); 
	auto maxHeightOfFont = ((screen_h-absYOffset - (border_h*2)) / font_h_px) / numWords; // 1 word per line
	auto fontSize = maxWidthOfFont > maxHeightOfFont ? maxHeightOfFont : maxWidthOfFont;

	screen->setTextSize(fontSize);

	byte bufIndex = 0;
	byte wordIndex = 0;
	byte wordNum = 0;
	while (buf[bufIndex] != '\0') {
		wordIndex = 0;
		wordNum++;

		while (buf[bufIndex] != '\0' && buf[bufIndex] != ' ' && buf[bufIndex] != '\n') {
			screenMessage[wordIndex++] = buf[bufIndex++];
		}
		if (buf[bufIndex] == ' ' || buf[bufIndex] == '\n') // skip over word separator
			bufIndex++;

		screenMessage[wordIndex] = '\0';
		
		auto text_width_px = fontSize * font_w_px * wordIndex;
		auto text_height_px = fontSize * font_h_px;
		auto x = (screen_w / 2) - (text_width_px / 2);
		auto y = ((wordNum * (screen_h+yOffset)) / (numWords+1)) - (text_height_px / 2);
		screen->setCursor(x, y);
		screen->print(screenMessage);
	}	
}

void effect(Adafruit_ST7735* screen, FunctionState* state, Preset* currentPreset) {
	EffectState* st = static_cast<EffectState*>(state);

	screen->fillScreen(!st->Bypassed() ? ST7735_RED : 0x59F);

	if (st->Name() != "") {
		screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, st->Name());
	}
}

void sceneSelect(Adafruit_ST7735* screen, FunctionState* state, Preset* currentPreset) {	
	SceneState* st = static_cast<SceneState*>(state);

	bool isSelected = currentPreset == nullptr ? false : currentPreset->getSelectedSceneNumber() == st->Scalar();
	screen->fillScreen(isSelected ? ST7735_RED : 0x59F);

	//screen->drawRect(0, 0, screen_w, screen_h, ST7735_RED);

	screen->setTextColor(ST7735_WHITE);

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
	PresetState* st = static_cast<PresetState*>(state);

	screen->fillScreen(0x87F0);//GREEN
	screen->setTextColor(ST7735_BLACK);//black
	sprintf(screenMessage, "%d", state->Type() == FunctionType::ftPresetDecrement ? st->PresetNumber() - st->Scalar() : st->PresetNumber() + st->Scalar());
	drawCentreString(screen, screenMessage);
}

void presetDisplay(Adafruit_ST7735* screen, FunctionState* state) {
	PresetState* st = static_cast<PresetState*>(state);

	screen->fillScreen(ST7735_BLACK);
	screen->setTextColor(ST7735_WHITE);	
	if (st->PresetName()[0] == '\0')
		sprintf(screenMessage, "%d", st->PresetNumber());	
	else
		sprintf(screenMessage, "%d: %s", st->PresetNumber(), st->PresetName());

	drawCentreString(screen, screenMessage);
}

void layoutSelect(Adafruit_ST7735* screen, FunctionState* state) {
	ScalarFunctionState* st = static_cast<ScalarFunctionState*>(state);
	screen->fillScreen(ST7735_RED);
	screen->setTextColor(ST7735_WHITE);
	sprintf(screenMessage, "Layout %d", st->Scalar());
	drawCentreString(screen, screenMessage);
}

char lastNote[2];
char lastFineTune;
bool hasCleared = false;
int noteFontSize = 6;
GFXcanvas1 tunerNoteCanvas(noteFontSize*font_w_px*2, screen_h / 2); 
void displayTuner(Adafruit_ST7735* screen, TunerData& tuner) {
	auto skipNoteDisplay = hasCleared && (tuner.Note[0] == lastNote[0] && tuner.Note[1] == lastNote[1]);
	lastNote[0] = tuner.Note[0];
	lastNote[1] = tuner.Note[1];	

	if (!hasCleared) {
		screen->fillScreen(ST7735_BLACK);
		hasCleared = true;
	}


	if (!skipNoteDisplay) {
		sprintf(screenMessage, "%s", tuner.Note);
		if (tuner.Note[1] == '#' || tuner.Note[1] == 'b') {
			screenMessage[2] = '\0';
		}
		else {
			screenMessage[1] = '\0';
		}
		//drawCentreString(screen, screenMessage, -40);
		tunerNoteCanvas.fillScreen(ST7735_BLACK);
		tunerNoteCanvas.setTextSize(noteFontSize);
		tunerNoteCanvas.setCursor(0, 10);
		tunerNoteCanvas.print(screenMessage);
		screen->drawBitmap((screen_w /2) -1 - noteFontSize*font_w_px/2, 0, tunerNoteCanvas.getBuffer(), noteFontSize*font_w_px*2, screen_h / 2, ST7735_GREEN, ST7735_BLACK);

		// Draw h ruler
		screen->fillRect(0, screen_h-50-1-3, screen_w, 3, ST7735_YELLOW);
	}
	
	if (lastFineTune != tuner.FineTune) {
		// black out last marker (more efficient than full screen)
		int x = (lastFineTune / 127.0) * screen_w;
		screen->fillCircle(x, screen_h - 25, 15, ST7735_BLACK);

		// draw center line
		screen->fillRect(screen_w/2-1-3, screen_h-50-1, 5, 50, ST7735_WHITE);

		// draw new marker
		lastFineTune = tuner.FineTune;
		auto tunerColour = tuner.FineTune > 60 && tuner.FineTune < 64 ? ST7735_GREEN : ST7735_RED;
		x = (tuner.FineTune / 127.0) * screen_w;
		screen->fillCircle(x, screen_h - 25, 15, tunerColour);
	}	
}

TftScreen::TftScreen(char screenNumber) {
	this->screenNumber = screenNumber;
	char cs_pin = screen_pins[screenNumber];
	this->screen = new Adafruit_ST7735(cs_pin, dc_pin, rst_pin);
	
	
	this->screen->initR(INITR_BLACKTAB);
	if (screenNumber == 7) {
		tunerNoteCanvas.setRotation(0);
	}
	
	if (screenNumber == screenToRotate) {
		this->screen->setRotation(3);
	}
	else {
		this->screen->setRotation(1);
	}
	this->screen->fillScreen(ST7735_BLACK);
}

void TftScreen::DisplayFunction(FunctionState* functionState, Preset* currentPreset, TunerData& tuner) {
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
	case FunctionType::ftPresetDisplay:
		presetDisplay(this->screen, functionState);
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
		drawCentreString(screen, "Tap");
		break;
	case FunctionType::ftTunerToggle:
		this->screen->fillScreen(ST7735_YELLOW);
		this->screen->setTextColor(ST7735_BLACK);
		drawCentreString(screen, "Tuner");
		break;
	case FunctionType::ftEffect:
		effect(this->screen, functionState, currentPreset);
		break;
	case FunctionType::ftMute:
		ToggleFunctionState* st = static_cast<ToggleFunctionState*>(functionState);
		this->screen->fillScreen(ST7735_WHITE);
		this->screen->setTextColor(ST7735_BLACK);
		drawCentreString(screen, st->Current() ? "Mute" : "Unmute");
		break;
	}
}

