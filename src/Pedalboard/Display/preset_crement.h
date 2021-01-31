#include "helper.h"

void presetCrement(TFT_eSPI* screen, FunctionState* state) {
	PresetState* st = static_cast<PresetState*>(state);

	screen->fillScreen(0x87F0);//GREEN
	screen->setTextColor(TFT_BLACK);//black
	sprintf(screenMessage, "%d", state->Type() == FunctionType::ftPresetDecrement ? st->PresetNumber() - st->Scalar() : st->PresetNumber() + st->Scalar());
	drawCentreString(screen, screenMessage);
}