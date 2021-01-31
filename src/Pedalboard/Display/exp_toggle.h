#include "helper.h"



void expToggle(TFT_eSPI* screen, FunctionState* state) {
	ExpressionFunctionState* st = static_cast<ExpressionFunctionState*>(state);
	auto selected = st->Selected();
	auto canvasHeight = screen_h / st->NumOfPedals();

	for (int i = 0; i < st->NumOfPedals(); i++) {
		auto sprite = TFT_eSprite(screen);
		sprite.setColorDepth(8);
		sprite.createSprite(screen_w, canvasHeight);
		sprite.fillSprite(selected == st->Pedals()[i] ? TFT_RED : TFT_WHITE);
		sprite.setTextSize(3);
		sprite.setTextFont(2);
		sprite.setTextColor(selected == st->Pedals()[i] ? TFT_WHITE : TFT_RED);

		auto expName = PedalSettings["expressionNames"][i];
		drawCentreString(&sprite, expName, screen_w, canvasHeight, 2, 2);

		sprite.pushSprite(0, i * canvasHeight);
	}
}
