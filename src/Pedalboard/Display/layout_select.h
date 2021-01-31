#include "helper.h"

void layoutSelect(TFT_eSPI* screen, FunctionState* state) {return;
	//screen->beginDraw();
	ScalarFunctionState* st = static_cast<ScalarFunctionState*>(state);
	screen->fillScreen(TFT_RED);
	screen->setTextColor(TFT_WHITE);
	sprintf(screenMessage, "Layout %d", st->Scalar());
	drawCentreString(screen, screenMessage);
	//screen->endDraw();
}
