#include "helper.h"

char lastNote[2];
char lastFineTune;
bool hasCleared = false;
const int noteFontSize = 6;
GFXcanvas1 tunerNoteCanvas(font_w_px*font_w_px*2, screen_h / 2); 

void displayTuner(Adafruit_GFX* screen, TunerData& tuner) {
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
