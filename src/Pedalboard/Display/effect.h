#include "helper.h"

void effect(GFrame* screen, FunctionState* state, Preset* currentPreset) {
	screen->beginDraw();

	EffectState* st = static_cast<EffectState*>(state);

	screen->fillScreen(!st->Bypassed() ? ST7735_RED : 0x59F);

	if (st->Name() != "") {
		screen->setTextColor(ST7735_WHITE);
		drawCentreString(screen, st->Name());
	}
	screen->endDraw();
}
