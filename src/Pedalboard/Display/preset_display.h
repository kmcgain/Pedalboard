#include "helper.h"


void presetDisplay(GFrame* screen, FunctionState* state) {
	screen->beginDraw();

	PresetState* st = static_cast<PresetState*>(state);

	screen->fillScreen(ST7735_BLACK);
	screen->setTextColor(ST7735_WHITE);	
	if (st->PresetName()[0] == '\0')
		sprintf(screenMessage, "%d", st->PresetNumber());	
	else
		sprintf(screenMessage, "%d: %s", st->PresetNumber(), st->PresetName());

	drawCentreString(screen, screenMessage);
	screen->endDraw();
}
