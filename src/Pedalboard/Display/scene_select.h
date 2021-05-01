#include "helper.h"
#include "colours.h"


void sceneSelect(TFT_eSPI* screen, FunctionState* state, Preset* currentPreset) {	
	SceneState* st = static_cast<SceneState*>(state);

	bool isSelected = currentPreset == nullptr ? false : currentPreset->getSelectedSceneNumber() == st->Scalar();
	screen->fillScreen(isSelected ? COLOUR_FG_TITLE : COLOUR_BG_PRIMARY);

	screen->setTextColor(isSelected ? COLOUR_BG_PRIMARY : COLOUR_FG_PRIMARY);
	screen->setTextSize(2);

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
