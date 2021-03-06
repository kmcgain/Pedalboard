#include "helper.h"


void presetDisplay(TFT_eSPI* screen, FunctionState* state) {
	screen->setTextSize(2);

	PresetState* st = static_cast<PresetState*>(state);

	screen->fillScreen(TFT_BLACK);
	screen->setTextColor(TFT_WHITE);	
	if (st->PresetName()[0] == '\0')
		sprintf(screenMessage, "%d", st->PresetNumber());	
	else
		sprintf(screenMessage, "%d: %s", st->PresetNumber(), st->PresetName());

	drawCentreStringNew(screen, screenMessage);
}
