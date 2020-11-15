#include "helper.h"

void expToggle(GFrame* screen, FunctionState* state) {
	ExpressionFunctionState* st = static_cast<ExpressionFunctionState*>(state);
	auto selected = st->Selected();

	screen->beginDraw();
	for (int i = 0; i < st->NumOfPedals(); i++) {
		auto canvasHeight = screen_h / st->NumOfPedals();
		GFXcanvas1 expCanvas(screen_w, canvasHeight);

		auto expName = PedalSettings["expressionNames"][i];
		drawCentreString(&expCanvas, expName, screen_w, canvasHeight, 2, 2);
		screen->drawBitmap(0, i * canvasHeight, expCanvas.getBuffer(), 
			screen_w, canvasHeight,  
			selected == st->Pedals()[i] ? ST7735_WHITE : ST7735_BLUE, 
			selected == st->Pedals()[i] ? ST7735_RED : ST7735_WHITE);
	}
	screen->endDraw();
}
