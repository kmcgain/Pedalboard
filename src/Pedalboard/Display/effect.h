#include "helper.h"

void effect(TFT_eSPI* screen, FunctionState* state, Preset* currentPreset) {
	EffectState* st = static_cast<EffectState*>(state);

	screen->fillScreen(!st->Bypassed() ? TFT_RED : 0x59F);

	if (st->Name() != "") {
		screen->setTextColor(TFT_WHITE);
		drawCentreString(screen, st->Name());
	}
}
