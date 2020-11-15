#include "helper.h"


void sceneSelect(GFrame* screen, FunctionState* state, Preset* currentPreset) {	
	screen->beginDraw();
	SceneState* st = static_cast<SceneState*>(state);

	bool isSelected = currentPreset == nullptr ? false : currentPreset->getSelectedSceneNumber() == st->Scalar();
	screen->fillScreen(isSelected ? ST7735_RED : 0x59F);

	//screen->drawRect(0, 0, screen_w, screen_h, ST7735_RED);

	screen->setTextColor(ST7735_WHITE);

	if (currentPreset != nullptr) {
		const char* sName = currentPreset->getSceneName(st->Scalar());
		if (sName != nullptr && sName[0] != '\0') {
			drawCentreString(screen, sName);
			return;
		}
	}

	sprintf(screenMessage, "%d", st->Scalar());
	drawCentreString(screen, screenMessage);	
	screen->endDraw();
}
