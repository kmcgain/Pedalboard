#include "helper.h"

void layoutSelect(GFrame* screen, FunctionState* state) {
	screen->beginDraw();
	ScalarFunctionState* st = static_cast<ScalarFunctionState*>(state);
	screen->fillScreen(ST7735_RED);
	screen->setTextColor(ST7735_WHITE);
	sprintf(screenMessage, "Layout %d", st->Scalar());
	drawCentreString(screen, screenMessage);
	screen->endDraw();
}
