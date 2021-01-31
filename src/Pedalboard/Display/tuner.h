#include "helper.h"

char lastNote[2];
char lastFineTune;
bool hasCleared = false;
const int noteFontSize = 6;
//GFXcanvas1 tunerNoteCanvas(font_w_px*font_w_px*2, screen_h / 2); 
TFT_eSprite* tunerNoteCanvas = NULL;

void displayTuner(TFT_eSPI* screen, TunerData& tuner) {
	if (tunerNoteCanvas == NULL) {
		tunerNoteCanvas = new TFT_eSprite(screen);
		tunerNoteCanvas->setColorDepth(8);
		tunerNoteCanvas->createSprite(screen_w, screen_h/2);
	}

	auto skipNoteDisplay = hasCleared && (tuner.Note[0] == lastNote[0] && tuner.Note[1] == lastNote[1]);
	lastNote[0] = tuner.Note[0];
	lastNote[1] = tuner.Note[1];	

	if (!hasCleared) {
		screen->fillScreen(TFT_BLACK); 
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

		tunerNoteCanvas->fillScreen(TFT_BLACK);
		tunerNoteCanvas->setTextSize(noteFontSize);
		tunerNoteCanvas->setTextFont(2);
		tunerNoteCanvas->setTextColor(TFT_GREEN);

		drawCentreString(tunerNoteCanvas, screenMessage, screen_w, screen_h/2);

		// Draw h ruler
		tunerNoteCanvas->fillRect(0, screen_h-50-1-3, screen_w, 3, TFT_YELLOW);
		
		tunerNoteCanvas->pushSprite(0, 0);
	}
	
	if (lastFineTune != tuner.FineTune) {
		// black out last marker (more efficient than full screen)
		int x = (lastFineTune / 127.0) * screen_w;
		
		screen->fillCircle(x, screen_h - 25, 15, TFT_BLACK);

		// draw center line
		screen->fillRect(screen_w/2-1-3, screen_h-50-1, 5, 50, TFT_WHITE);

		// draw new marker
		lastFineTune = tuner.FineTune;
		auto tunerColour = tuner.FineTune > 60 && tuner.FineTune < 64 ? TFT_GREEN : TFT_RED;
		x = (tuner.FineTune / 127.0) * screen_w;
		screen->fillCircle(x, screen_h - 25, 15, tunerColour);
	}
}
