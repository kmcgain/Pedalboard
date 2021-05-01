#include "helper.h"
#include "colours.h"


void expToggle(TFT_eSPI* screen, FunctionState* state) {
	ExpressionFunctionState* st = static_cast<ExpressionFunctionState*>(state);
	auto selected = st->Selected();
	auto canvasHeight = screen_h / st->NumOfPedals();

	for (int i = 0; i < st->NumOfPedals(); i++) {
		auto sprite = TFT_eSprite(screen);
		sprite.setColorDepth(8);
		sprite.createSprite(screen_w, canvasHeight);
		sprite.fillSprite(selected == st->Pedals()[i] ? COLOUR_FG_TITLE : COLOUR_BG_PRIMARY);
		sprite.setTextSize(3);
		sprite.setTextFont(2);
		sprite.setTextColor(selected == st->Pedals()[i] ? COLOUR_BG_PRIMARY : COLOUR_FG_PRIMARY);

		auto expName = PedalSettings["expressionNames"][i];
		drawCentreString(&sprite, expName, screen_w, canvasHeight, 2, 2);

		sprite.pushSprite(0, i * canvasHeight);
	}
}
