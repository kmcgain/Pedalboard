#include "helper.h"

void presetCrement(GFrame* screen, FunctionState* state) {	
	screen->beginDraw();

	PresetState* st = static_cast<PresetState*>(state);

	screen->fillScreen(0x87F0);//GREEN
	screen->setTextColor(ST7735_BLACK);//black
	sprintf(screenMessage, "%d", state->Type() == FunctionType::ftPresetDecrement ? st->PresetNumber() - st->Scalar() : st->PresetNumber() + st->Scalar());
	drawCentreString(screen, screenMessage);
	screen->endDraw();
}