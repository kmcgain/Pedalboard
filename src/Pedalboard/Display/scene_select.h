#include "helper.h"


void sceneSelect(TFT_eSPI* screen, FunctionState* state, Preset* currentPreset) {	
	SceneState* st = static_cast<SceneState*>(state);

	bool isSelected = currentPreset == nullptr ? false : currentPreset->getSelectedSceneNumber() == st->Scalar();
	screen->fillScreen(isSelected ? TFT_RED : 0x59F);

	screen->setTextColor(TFT_WHITE);

	if (currentPreset != nullptr) {
		const char* sName = currentPreset->getSceneName(st->Scalar());
		if (sName != nullptr && sName[0] != '\0') {
			drawCentreString(screen, sName);
			return;
		}
	}

	sprintf(screenMessage, "%d", st->Scalar());
	drawCentreString(screen, screenMessage);	
}
